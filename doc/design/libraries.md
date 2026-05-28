# Sixbit Core — Libraries

## Overview

| Name | Description |
|------|-------------|
| libsixbit_cli | RPC client functionality used by sixbit-cli |
| libsixbit_common | Shared higher-level functionality |
| libsixbit_consensus | Consensus logic |
| libsixbit_crypto | Cryptographic primitives |
| libsixbit_kernel | Consensus engine |
| libsixbitqt | GUI functionality |
| libsixbit_ipc | IPC communication |
| libsixbit_node | P2P + RPC server |
| libsixbit_util | Low-level utilities |
| libsixbit_wallet | Wallet logic |
| libsixbit_wallet_tool | Wallet tools |
| libsixbit_zmq | ZeroMQ notifications |

---

## Conventions

- Libraries are internal and APIs are unstable
- Each library should map to a directory and namespace:

Examples:

- node ? src/node (node::)
- wallet ? src/wallet (wallet::)
- ipc ? src/ipc (ipc::)
- util ? src/util (util::)
- consensus ? src/consensus (Consensus::)

---

## Dependency Rules

- Minimize dependencies
- Follow strict layering

### Key Principles

- libsixbit_crypto ? no dependencies
- libsixbit_util ? depends only on crypto
- libsixbit_consensus ? depends only on crypto
- libsixbit_common ? depends on util + consensus + crypto
- libsixbit_kernel ? depends on util + consensus + crypto
- libsixbit_node ? depends on kernel + common + util + crypto
- libsixbit_wallet ? depends on common + util + crypto
- libsixbitqt ? depends on common + util

---

## Architecture Notes

- Wallet, node, and GUI must NOT directly depend on each other
- Communication happens via interfaces in:

src/interfaces/

---

## Design Goals

- modularity
- minimal coupling
- clear layering
- future kernel isolation

---

## Work in Progress

- Moving validation logic into libsixbit_kernel
