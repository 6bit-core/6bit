# Sixbit Core — Multiprocess Design Document

Guide to the design and architecture of the Sixbit Core multiprocess feature

_This document describes the design of the multiprocess feature. For usage information, see the top-level multiprocess.md file._

---

## Introduction

Sixbit Core historically used a monolithic architecture combining node, wallet, and GUI.

This design introduces a modular architecture to improve:

- security
- scalability
- maintainability

---

## Current Architecture

Executables:

- sixbitd — node + RPC + wallet
- sixbit-qt — GUI + node + wallet

Limitations:

- tightly coupled components
- increased attack surface
- limited flexibility

---

## Proposed Architecture

Split into:

- sixbit-node — P2P + RPC + indexes
- sixbit-wallet — wallet logic
- sixbit-gui — GUI

Benefits:

- process isolation
- independent execution
- distributed deployment

---

## IPC Overview

Communication uses:

- UNIX sockets
- Cap’n Proto RPC
- libmultiprocess

Flow:

wallet ? node  
gui ? node  

---

## Core Components

### Interfaces

Located in:

src/interfaces/

Defines abstract communication layers.

---

### Cap’n Proto

Located in:

src/ipc/capnp/

Defines message schemas.

---

### mpgen Tool

Generates:

- client classes
- server classes
- serialization logic

---

### libmultiprocess

Handles:

- process spawning
- IPC wiring
- threading

---

## Design Principles

- IPC hidden from core logic
- Interfaces behave like normal C++ calls
- Thread-safe communication model
- Optional build support

---

## Security Considerations

- Increased attack surface via IPC
- UNIX socket exposure risk
- External dependencies (Cap’n Proto)

Mitigation:

- optional IPC disable
- local-only sockets
- sandboxing (future)

---

## Example Flow

Wallet requests block hash:

1. Wallet calls interface method
2. Client proxy serializes request
3. Node receives request
4. Executes locally
5. Returns result

---

## Future Enhancements

- Separate index processes
- Independent RPC endpoints
- Interface stabilization
- sandboxing support

---

## Conclusion

Multiprocess architecture improves:

- modularity
- security
- flexibility

---

## References

- https://capnproto.org
- https://github.com/sixbit-core/libmultiprocess

