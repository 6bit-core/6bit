#!/usr/bin/env bash
set -euo pipefail

if ! command -v brew >/dev/null 2>&1; then
  echo "Install Homebrew first: https://brew.sh"
  exit 1
fi

brew update
brew install cmake ninja pkg-config automake libtool gnu-getopt coreutils \
  boost libevent sqlite qt@6 qrencode zeromq

echo "macOS build dependencies installed."
