This folder contains lint scripts.

Running locally
===============

To run linters locally using the same versions as the CI environment, use the
included Dockerfile:

```sh
DOCKER_BUILDKIT=1 docker build -t sixbit-linter --file "./ci/lint_imagefile" ./ && docker run --rm -v "$(pwd):/sixbit" -it sixbit-linter
```

Rebuilding the container each time is fine, because it is fast when cached and
helps avoid issues when the image changes.

Test runner
===========

To run all lint checks in the test runner outside Docker, first install the Rust
toolchain using your package manager of choice or
https://www.rust-lang.org/tools/install

Then run:

```sh
( cd ./test/lint/test_runner/ && cargo fmt && cargo clippy && RUST_BACKTRACE=1 cargo run )
```

To run individual lint checks, pass `--lint=TEST_TO_RUN`:

```sh
( cd ./test/lint/test_runner/ && RUST_BACKTRACE=1 cargo run -- --lint=doc --lint=trailing_whitespace )
```

Dependencies
------------

See CI setup: ../../ci/lint/01_install.sh

Running tests
-------------

Example:

```sh
test/lint/lint-files.py
```

git-subtree-check.sh
====================

Usage:

test/lint/git-subtree-check.sh [-r] DIR [COMMIT]
