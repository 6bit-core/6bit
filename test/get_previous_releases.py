#!/usr/bin/env python3
#
# Copyright (c) 2018-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.
#
# Download or build previous releases.
# Needs curl and tar to download a release, or the build dependencies when
# building a release.

import argparse
from collections.abc import Iterator
import contextlib
from fnmatch import fnmatch
import hashlib
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys
import time
import urllib.request
import zipfile

SHA256_SUMS = {}


def version_key(tag: str) -> tuple[int, int, int, int]:
    """Parse tags like v23, v23.1, v23.2.1, v25.0rc2 into comparable tuples."""
    m = re.fullmatch(r"v(\d+)(?:\.(\d+))?(?:\.(\d+))?(?:rc(\d+))?", tag)
    if not m:
        raise ValueError(f"Unrecognized tag format: {tag}")
    major = int(m.group(1) or 0)
    minor = int(m.group(2) or 0)
    patch = int(m.group(3) or 0)
    rc = int(m.group(4) or 9999)
    return (major, minor, patch, rc)


@contextlib.contextmanager
def pushd(new_dir: str | os.PathLike[str]) -> Iterator[None]:
    previous_dir = os.getcwd()
    os.chdir(new_dir)
    try:
        yield
    finally:
        os.chdir(previous_dir)


def download_from_url(url, archive):
    last_print_time = time.time()

    def progress_hook(progress_bytes, total_size):
        nonlocal last_print_time
        now = time.time()
        if total_size > 0:
            percent = min(100, (progress_bytes * 100) / total_size)
        else:
            percent = 0
        bar_length = 40
        filled_length = int(bar_length * percent / 100)
        bar = '#' * filled_length + '-' * (bar_length - filled_length)
        if now - last_print_time >= 1 or percent >= 100:
            print(f'\rDownloading: [{bar}] {percent:.1f}%', flush=True, end="")
            last_print_time = now

    with urllib.request.urlopen(url) as response:
        if response.status != 200:
            raise RuntimeError(f"HTTP request failed with status code: {response.status}")

        total_size = int(response.getheader('Content-Length', 0))
        progress_bytes = 0

        with open(archive, 'wb') as file:
            while True:
                chunk = response.read(8192)
                if not chunk:
                    break
                file.write(chunk)
                progress_bytes += len(chunk)
                progress_hook(progress_bytes, total_size)

    print('\n', flush=True, end="")


def download_binary(tag, args) -> int:
    if Path(tag).is_dir():
        if not args.remove_dir:
            print(f'Using cached {tag}')
            return 0
        shutil.rmtree(tag)

    bin_path = f'bin/sixbit-core-{tag[1:]}'

    match = re.compile(r'v(.*)(rc[0-9]+)$').search(tag)
    if match:
        bin_path = f'bin/sixbit-core-{match.group(1)}/test.{match.group(2)}'

    host = args.host
    if version_key(tag) < version_key("v23") and host in ["x86_64-apple-darwin", "arm64-apple-darwin"]:
        host = "osx64"

    archive_format = 'tar.gz'
    if host == 'win64':
        archive_format = 'zip'

    archive = f'sixbit-{tag[1:]}-{host}.{archive_format}'
    archive_url = f'https://6bit.dev/{bin_path}/{archive}'

    print(f'Fetching: {archive_url}')

    try:
        download_from_url(archive_url, archive)
    except Exception as e:
        print(f"\nDownload failed: {e}", file=sys.stderr)
        return 1

    hasher = hashlib.sha256()
    with open(archive, "rb") as afile:
        hasher.update(afile.read())
    archive_hash = hasher.hexdigest()

    if archive_hash not in SHA256_SUMS or SHA256_SUMS[archive_hash]['archive'] != archive:
        if archive in [v['archive'] for v in SHA256_SUMS.values()]:
            print(f"Checksum {archive_hash} did not match", file=sys.stderr)
        else:
            print("Checksum for given version doesn't exist", file=sys.stderr)
        return 1

    print("Checksum matched")
    Path(tag).mkdir()

    if host == 'win64':
        try:
            with zipfile.ZipFile(archive, 'r') as zf:
                zf.extractall(tag)
            extracted_items = os.listdir(tag)
            top_level_dir = os.path.join(tag, extracted_items[0])
            for item in os.listdir(top_level_dir):
                shutil.move(os.path.join(top_level_dir, item), tag)
            os.rmdir(top_level_dir)
        except Exception as e:
            print(f"Zip extraction failed: {e}", file=sys.stderr)
            return 1
    else:
        ret = subprocess.run(
            ['tar', '-zxf', archive, '-C', tag, '--strip-components=1', f'sixbit-{tag[1:]}']
        ).returncode
        if ret != 0:
            print(f"Failed to extract the {tag} tarball", file=sys.stderr)
            return ret

    Path(archive).unlink()

    if version_key(tag) >= version_key("v23") and version_key(tag) < version_key("v28.2") and args.host == "arm64-apple-darwin":
        binary_path = f'{os.getcwd()}/{tag}/bin/'

        for arm_binary in os.listdir(binary_path):
            ret = subprocess.run(
                ['codesign', '-v', binary_path + arm_binary],
                stderr=subprocess.DEVNULL,
            ).returncode
            if ret == 1:
                ret = subprocess.run(
                    ['codesign', '-s', '-', binary_path + arm_binary]
                ).returncode
                if ret != 0:
                    print(f"Failed to self-sign {tag} {arm_binary} arm64 binary", file=sys.stderr)
                    return 1

                ret = subprocess.run(
                    ['codesign', '-v', binary_path + arm_binary]
                ).returncode
                if ret != 0:
                    print(f"Failed to verify the self-signed {tag} {arm_binary} arm64 binary", file=sys.stderr)
                    return 1

    return 0


def set_host(args) -> int:
    if platform.system().lower() == 'windows':
        if platform.machine() != 'AMD64':
            print('Only 64bit Windows supported', file=sys.stderr)
            return 1
        args.host = 'win64'
        return 0

    host = os.environ.get(
        'HOST',
        subprocess.check_output(['./depends/config.guess'], text=True).strip(),
    )

    platforms = {
        'aarch64-*-linux*': 'aarch64-linux-gnu',
        'powerpc64le-*-linux-*': 'powerpc64le-linux-gnu',
        'riscv64-*-linux*': 'riscv64-linux-gnu',
        'x86_64-*-linux*': 'x86_64-linux-gnu',
        'x86_64-apple-darwin*': 'x86_64-apple-darwin',
        'aarch64-apple-darwin*': 'arm64-apple-darwin',
    }
    args.host = ''
    for pattern, target in platforms.items():
        if fnmatch(host, pattern):
            args.host = target
    if not args.host:
        print(f'Not sure which binary to download for {host}', file=sys.stderr)
        return 1
    return 0


def main(args) -> int:
    Path(args.target_dir).mkdir(exist_ok=True, parents=True)
    print(f"Releases directory: {args.target_dir}")
    ret = set_host(args)
    if ret:
        return ret
    with pushd(args.target_dir):
        for tag in args.tags:
            ret = download_binary(tag, args)
            if ret:
                return ret
    return 0


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        epilog=(
            "HOST can be set to any of the `host-platform-triplet`s from\n"
            "depends/README.md for which a release exists."
        ),
    )
    parser.add_argument('-r', '--remove-dir', action='store_true',
                        help='remove existing directory.')
    parser.add_argument('-t', '--target-dir', action='store',
                        help='target directory.', default='releases')
    all_tags = sorted([*set([v['tag'] for v in SHA256_SUMS.values()])], key=version_key)
    parser.add_argument('tags', nargs='*', default=all_tags,
                        help='release tags. e.g.: v0.18.1 v0.20.0rc2 '
                        '(if not specified, the full list needed for '
                        'backwards compatibility tests will be used)')
    args = parser.parse_args()
    sys.exit(main(args))
