# Sixbit Core — macOS Build Guide

**Updated for macOS 15 (Sequoia)**

This guide describes how to build sixbitd, command-line utilities, and GUI on macOS.

---

## Preparation

### Terminal

/Applications/Utilities/Terminal.app

---

## 1. Xcode Command Line Tools

Install:

xcode-select --install

---

## 2. Homebrew

Install from: https://brew.sh

---

## 3. Required Dependencies

brew install cmake boost pkgconf libevent capnp

---

### Wallet

Disable if not needed:

-DENABLE_WALLET=OFF

---

### IPC

Disable if not needed:

-DENABLE_IPC=OFF

---

## 4. Clone Repository

git clone https://github.com/sixbit-core/sixbit.git
cd sixbit

---

## 5. Optional Dependencies

### Qt GUI

brew install qt@6

Enable:

-DBUILD_GUI=ON

---

### QR Encode

brew install qrencode

Disable:

-DWITH_QRENCODE=OFF

---

### ZMQ

brew install zeromq

---

### Test Suite

brew install python

---

## Build

### Configure

cmake -B build -DBUILD_GUI=ON

OR

cmake -B build -DENABLE_WALLET=OFF -DBUILD_GUI=OFF

---

### Compile

cmake --build build
ctest --test-dir build

---

### Deploy

cmake --build build --target deploy

---

## Run

./build/bin/sixbitd
./build/bin/sixbit-qt

---

## Data Directory

~/Library/Application Support/sixbit/

---

## Config File

mkdir -p "~/Library/Application Support/sixbit"
touch "~/Library/Application Support/sixbit/sixbit.conf"
chmod 600 "~/Library/Application Support/sixbit/sixbit.conf"

---

## Logs

tail -f ~/Library/Application\ Support/sixbit/debug.log

---

## Commands

./build/bin/sixbitd -daemon
./build/bin/sixbit-cli help
./build/bin/sixbit-qt -server

---

Done.
