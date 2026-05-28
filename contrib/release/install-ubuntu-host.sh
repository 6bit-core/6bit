#!/usr/bin/env bash
set -euo pipefail

sudo apt update

sudo apt install -y \
  build-essential cmake ninja-build git curl ca-certificates python3 pkg-config \
  g++-mingw-w64-x86-64 mingw-w64 nsis \
  automake libtool bison gperf gettext yasm texinfo help2man \
  libevent-dev libboost-dev libsqlite3-dev

echo "Ubuntu build dependencies installed."
