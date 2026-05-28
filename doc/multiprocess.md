cat > multiprocess.md << 'EOF'
# Sixbit Core — Multiprocess Guide

This document describes how to build and use the multiprocess architecture in Sixbit Core.

For design details, see `design/multiprocess.md`.

---

## Overview

Multiprocess mode separates Sixbit Core into multiple executables:

- sixbit-node — P2P and RPC logic  
- sixbit-wallet — wallet functionality  
- sixbit-gui — graphical interface  

Benefits include:

- improved security through process isolation  
- better stability via fault containment  
- flexible modular deployment  

---

## Build Configuration

Enable multiprocess support with:

-DENABLE_IPC=ON

Enabled by default on Unix systems.

---

## Dependencies

Multiprocess support requires:

- Cap’n Proto  
- libmultiprocess  

FreeBSD install:

pkg install capnproto

---

## Debugging IPC

-debug=ipc

---

## Build Methods

### Standard Build

cmake -B build -DENABLE_IPC=ON  
cmake --build build  

---

### Using Depends System

cd <sixbit_SOURCE_DIRECTORY>  
make -C depends NO_QT=1  

HOST_PLATFORM="x86_64-pc-linux-gnu"  

cmake -B build \
  --toolchain=depends/$HOST_PLATFORM/toolchain.cmake  

cmake --build build  

Run:

build/bin/sixbit -m node -regtest -printtoconsole -debug=ipc  

---

## Running Multiprocess Mode

sixbit -m node -debug=ipc  

GUI:

sixbit -m gui -printtoconsole -debug=ipc  

---

## Summary

Multiprocess mode provides:

- modular architecture  
- strong isolation  
- future scalability  

EOF
