# Copyright (c) 2019-present The Bitcoin Core developers
#!/usr/bin/env python3
# Copyright (c) 2026-present The Sixbit Core Developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/

import argparse
import os
import re
import subprocess
import sys
import tempfile

BINARIES = [
    "bin/sixbit",
    "bin/sixbitd",
    "bin/sixbit-cli",
    "bin/sixbit-tx",
    "bin/sixbit-wallet",
    "bin/sixbit-util",
    "bin/sixbit-qt",
]

parser = argparse.ArgumentParser(
    formatter_class=argparse.RawDescriptionHelpFormatter,
)
parser.add_argument(
    "-s",
    "--skip-missing-binaries",
    action="store_true",
    default=False,
    help="skip generation for binaries that are not found in the build path",
)
args = parser.parse_args()

git = os.getenv("GIT", "git")
help2man = os.getenv("HELP2MAN", "help2man")

topdir = os.getenv("TOPDIR")
if not topdir:
    r = subprocess.run(
        [git, "rev-parse", "--show-toplevel"],
        capture_output=True,
        check=True,
        text=True,
    )
    topdir = r.stdout.rstrip()

builddir = os.getenv("BUILDDIR", os.path.join(topdir, "build"))
mandir = os.getenv("MANDIR", os.path.join(topdir, "doc/man"))

os.makedirs(mandir, exist_ok=True)

versions = []
for relpath in BINARIES:
    abspath = os.path.join(builddir, relpath)
    try:
        r = subprocess.run(
            [abspath, "--version"],
            capture_output=True,
            check=True,
            text=True,
        )
    except OSError:
        if args.skip_missing_binaries:
            print(f"{abspath} not found or not an executable. Skipping...", file=sys.stderr)
            continue
        print(f"{abspath} not found or not an executable", file=sys.stderr)
        sys.exit(1)
    except subprocess.CalledProcessError:
        print(f"{abspath} failed when run with --version", file=sys.stderr)
        sys.exit(1)

    lines = r.stdout.splitlines()
    if not lines:
        print(f"{abspath} produced no output for --version", file=sys.stderr)
        sys.exit(1)

    output = lines[0]
    search = re.search(r"v[0-9]\S+", output)
    if not search:
        print(f"Could not parse version string from: {abspath}", file=sys.stderr)
        sys.exit(1)

    verstr = search.group(0)
    copyright_lines = lines[1:]

    if not copyright_lines or not copyright_lines[0].startswith("Copyright (C)"):
        print(f"Could not extract copyright message from: {abspath}", file=sys.stderr)
        sys.exit(1)

    versions.append((abspath, verstr, copyright_lines))

if not versions:
    print(
        f"No binaries found in {builddir}. Please ensure the binaries are present "
        f"in {builddir}, or set another build path using the BUILDDIR env variable.",
        file=sys.stderr,
    )
    sys.exit(1)

if any(verstr.endswith("-dirty") for (_, verstr, _) in versions):
    print("WARNING: Binaries were built from a dirty tree.")
    print("man pages generated from dirty binaries should NOT be committed.")
    print("To properly generate man pages, please commit your changes (or discard them), rebuild, then run this script again.")
    print()

with tempfile.NamedTemporaryFile("w", suffix=".h2m") as footer:
    footer.write("[COPYRIGHT]\n")
    footer.write("\n".join(versions[0][2]).strip())
    footer.write("\n[SEE ALSO]\n")
    footer.write(", ".join(os.path.basename(path) + "(1)" for (path, _, _) in versions))
    footer.write("\n")
    footer.flush()

    for (abspath, verstr, _) in versions:
        outname = os.path.join(mandir, os.path.basename(abspath) + ".1")
        print(f"Generating {outname}...")
        subprocess.run(
            [
                help2man,
                "-N",
                f"--version-string={verstr}",
                f"--include={footer.name}",
                "-o",
                outname,
                abspath,
            ],
            check=True,
        )
