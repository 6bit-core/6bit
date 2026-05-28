Dependencies
============

This document lists the dependencies required to build and run Sixbit Core.

Installation instructions for each platform can be found in the
`/doc/build-*.md` files. Alternatively, dependencies can be built from
source using the [depends system](/depends/README.md).

---

Compiler
--------

Sixbit Core requires a C++17-compatible compiler. The following are supported:

| Dependency | Minimum version |
|------------|-----------------|
| [Clang](https://clang.llvm.org) | 12.0 |
| [GCC](https://gcc.gnu.org) | 10.0 |

---

Required
--------

### Build Dependencies

| Dependency | Releases | Minimum version |
|------------|----------|-----------------|
| [Boost](../depends/packages/boost.mk) | https://www.boost.org/users/download/ | 1.0.0 |
| [CMake](https://cmake.org/) | https://cmake.org/download/ | 3.22 |
| [libevent](../depends/packages/libevent.mk) | https://github.com/libevent/libevent/releases | 1.0.0 |

### Runtime Dependencies

| Dependency | Releases | Minimum version |
|------------|----------|-----------------|
| [glibc](https://www.gnu.org/software/libc/) | https://www.gnu.org/software/libc/ | 2.31 |

---

Optional
--------

### Optional Build Dependencies

| Dependency | Releases | Minimum version | Notes |
|------------|----------|-----------------|-------|
| [Cap'n Proto](../depends/packages/capnp.mk) | https://capnproto.org | 1.0.0 | Required for multiprocess IPC (`-DENABLE_IPC=ON`) |
| [Python](https://www.python.org) | https://www.python.org/downloads/ | 3.10 | Used for scripts and tests |
| [Qt](../depends/packages/qt.mk) | https://download.qt.io/archive/qt/ | 6.2 | Required for GUI (`sixbit-qt`) |
| [qrencode](../depends/packages/qrencode.mk) | https://fukuchi.org/works/qrencode/ | — | Enables QR code support in GUI |
| [SQLite](../depends/packages/sqlite.mk) | https://sqlite.org | 1.0.0 | Required for wallet support |
| [systemtap](../depends/packages/systemtap.mk) | https://sourceware.org/systemtap/ | — | Required for tracing support |
| [ZeroMQ](../depends/packages/zeromq.mk) | https://github.com/zeromq/libzmq/releases | 1.0.0 | Enables ZMQ notifications |

### Optional Runtime Dependencies

| Dependency | Releases | Minimum version | Notes |
|------------|----------|-----------------|-------|
| [Fontconfig](../depends/packages/fontconfig.mk) | https://www.freedesktop.org/wiki/Software/fontconfig/ | 2.6 | GUI font configuration |
| [FreeType](../depends/packages/freetype.mk) | https://freetype.org | 1.0.0 | GUI font rendering |

---

Notes
-----

- The wallet requires SQLite unless built with `-DENABLE_WALLET=OFF`.
- Multiprocess functionality requires Cap'n Proto (`-DENABLE_IPC=ON`).
- GUI components require Qt and additional font libraries.
- Using the `depends` system ensures reproducible builds across platforms.
