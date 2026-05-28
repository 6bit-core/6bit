#!/usr/bin/env bash
set -euo pipefail

PROJECT_NAME="6bit"
VERSION="${VERSION:-1.0.0}"
JOBS="${JOBS:-$(nproc 2>/dev/null || sysctl -n hw.ncpu)}"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
DIST_DIR="$ROOT_DIR/dist"
DEPENDS_DIR="$ROOT_DIR/depends"

mkdir -p "$DIST_DIR"

usage() {
  cat <<EOF
Usage:
  ./contrib/release/build-release.sh linux
  ./contrib/release/build-release.sh windows
  ./contrib/release/build-release.sh macos
  ./contrib/release/build-release.sh all

Env:
  VERSION=1.0.0
  JOBS=8
  SIGN=0
EOF
}

build_depends() {
  local host="$1"
  echo "==> Building depends for $host"
  make -C "$DEPENDS_DIR" HOST="$host" -j"$JOBS"
}

configure_and_build() {
  local name="$1"
  local toolchain="$2"
  local build_dir="$ROOT_DIR/build-$name"

  echo "==> Configuring $name"
  rm -rf "$build_dir"

  cmake -B "$build_dir" -G Ninja \
    ${toolchain:+--toolchain "$toolchain"} \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_GUI=ON \
    -DBUILD_WALLET=ON \
    -DENABLE_IPC=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_BENCH=OFF

  echo "==> Building $name"
  cmake --build "$build_dir" -j"$JOBS"

  echo "==> Installing $name"
  rm -rf "$DIST_DIR/$name"
  cmake --install "$build_dir" --prefix "$DIST_DIR/$name"

  echo "==> Packaging $name"
  tar -C "$DIST_DIR" -czf "$DIST_DIR/${PROJECT_NAME}-${VERSION}-${name}.tar.gz" "$name"
}

build_linux() {
  build_depends "x86_64-pc-linux-gnu"
  configure_and_build "linux-x86_64" "$DEPENDS_DIR/x86_64-pc-linux-gnu/toolchain.cmake"
}

build_windows() {
  build_depends "x86_64-w64-mingw32"
  configure_and_build "win64" "$DEPENDS_DIR/x86_64-w64-mingw32/toolchain.cmake"

  if command -v makensis >/dev/null 2>&1; then
    echo "==> NSIS available. You may also build the deploy target:"
    echo "    cmake --build build-win64 --target deploy"
  fi
}

build_macos() {
  # Native macOS build. For cross-building macOS from Linux, use Guix or provide a valid macOS SDK.
  build_depends "x86_64-apple-darwin"
  configure_and_build "macos-x86_64" "$DEPENDS_DIR/x86_64-apple-darwin/toolchain.cmake"
}

case "${1:-}" in
  linux) build_linux ;;
  windows|win64) build_windows ;;
  macos|darwin) build_macos ;;
  all)
    build_linux
    build_windows
    if [[ "$(uname -s)" == "Darwin" ]]; then
      build_macos
    else
      echo "Skipping macOS native build on non-macOS host. Use Guix or build on macOS."
    fi
    ;;
  *) usage; exit 1 ;;
esac

echo "==> Done. Artifacts are in: $DIST_DIR"
