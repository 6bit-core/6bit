#!/usr/bin/env python3

import json
import subprocess
import sys
from pathlib import Path


def main():
    """Tests ordered roughly from faster to slower."""
    expect_code(run_verify([], "pub", ["9.9.9-does-not-exist"]), 4, "Nonexistent version should fail")
    expect_code(run_verify([], "pub", ["bad.version.string"]), 11, "Malformed version should fail")
    expect_code(run_verify(["--min-good-sigs", "20"], "pub", ["0.1.0"]), 9, "--min-good-sigs 20 should fail")

    print("- testing verification (0.1.0-x86_64-linux-gnu.tar.gz)", flush=True)
    rel = run_verify(["--json"], "pub", ["0.1.0-x86_64-linux-gnu.tar.gz"])
    try:
        result = json.loads(rel.stdout.decode())
    except Exception:
        print("failed on 0.1.0-x86_64-linux-gnu.tar.gz --json:")
        print_process_failure(rel)
        raise

    expect_code(rel, 0, "0.1.0-x86_64-linux-gnu.tar.gz should succeed")
    v = result["verified_binaries"]
    assert result["good_trusted_sigs"]
    assert len(v) == 1
    assert v["sixbit-0.1.0-x86_64-linux-gnu.tar.gz"] == "REPLACE_WITH_REAL_HASH"

    print("- testing verification (0.1.0)", flush=True)
    rel_all = run_verify(["--json"], "pub", ["0.1.0"])
    try:
        result = json.loads(rel_all.stdout.decode())
    except Exception:
        print("failed on 0.1.0 --json:")
        print_process_failure(rel_all)
        raise

    expect_code(rel_all, 0, "0.1.0 should succeed")
    v = result["verified_binaries"]
    assert result["good_trusted_sigs"]
    assert v["sixbit-0.1.0-aarch64-linux-gnu.tar.gz"] == "REPLACE_WITH_REAL_HASH"
    assert v["sixbit-0.1.0-x86_64-linux-gnu.tar.gz"] == "REPLACE_WITH_REAL_HASH"


def run_verify(global_args: list[str], command: str, command_args: list[str]) -> subprocess.CompletedProcess:
    maybe_here = Path.cwd() / "verify.py"
    path = maybe_here if maybe_here.exists() else Path.cwd() / "contrib" / "verify-binaries" / "verify.py"

    args = [str(path), *global_args, command]
    if command == "pub":
        args.append("--cleanup")
    args.extend(command_args)

    return subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def expect_code(completed: subprocess.CompletedProcess, expected_code: int, msg: str):
    if completed.returncode != expected_code:
        print(f"{msg!r} failed: got code {completed.returncode}, expected {expected_code}")
        print_process_failure(completed)
        sys.exit(1)
    print(f"? {msg!r} passed")


def print_process_failure(completed: subprocess.CompletedProcess):
    print(f"stdout:\n{completed.stdout.decode()}")
    print(f"stderr:\n{completed.stderr.decode()}")


if __name__ == "__main__":
    main()
