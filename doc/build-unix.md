# UNIX BUILD NOTES

Some notes on how to build Sixbit Core in Unix.

## To Build

```bash
cmake -B build
cmake --build build
cmake --install build
```

## Memory Requirements

- Recommended: 1.5 GB RAM
- Reduce memory usage:

```bash
cmake -B build -DCMAKE_CXX_FLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768"
```

Disable debug symbols:

```bash
cmake -B build -DCMAKE_CXX_FLAGS_RELWITHDEBINFO="-O2 -g0"
```

Use clang:

```bash
cmake -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
```

## Ubuntu / Debian

```bash
sudo apt-get install build-essential cmake pkgconf python3
sudo apt-get install libevent-dev libboost-dev
sudo apt install libsqlite3-dev
sudo apt-get install libcapnp-dev capnproto
sudo apt-get install libzmq3-dev
sudo apt install systemtap-sdt-dev
```

GUI:
```bash
sudo apt-get install qt6-base-dev qt6-tools-dev qt6-l10n-tools qt6-tools-dev-tools libgl-dev
sudo apt install qt6-wayland
sudo apt-get install libqrencode-dev
```

## Fedora

```bash
sudo dnf install gcc-c++ cmake make python3
sudo dnf install libevent-devel boost-devel
sudo dnf install sqlite-devel
sudo dnf install zeromq-devel
sudo dnf install systemtap-sdt-devel
sudo dnf install capnproto capnproto-devel
```

GUI:
```bash
sudo dnf install qt6-qtbase-devel qt6-qttools-devel
sudo dnf install qt6-qtwayland
sudo dnf install qrencode-devel
```

## Alpine

```bash
apk add build-base cmake linux-headers pkgconf python3
apk add libevent-dev boost-dev
apk add sqlite-dev
apk add capnproto capnproto-dev
apk add zeromq-dev
```

GUI:
```bash
apk add qt6-qtbase-dev qt6-qttools-dev
apk add libqrencode-dev
```

## Disable Wallet

```bash
cmake -B build -DENABLE_WALLET=OFF
```

## Arch Example

```bash
pacman --sync --needed capnproto cmake boost gcc git libevent make python sqlite
git clone https://github.com/6bit-core/6bit.git
cd sixbit/
cmake -B build
cmake --build build
ctest --test-dir build
./build/bin/sixbit
```
