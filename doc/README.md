# Sixbit Core

Sixbit Core is the reference implementation of the sixbit network, providing full node functionality, wallet support, and a graphical user interface.

---

## Setup

Sixbit Core builds the backbone of the sixbit network. It downloads and, by default, stores the entire history of transactions.

Currently, it requires minimal disk space, but this will grow over time as the network expands. Synchronization time depends on your system and network speed.

Download Sixbit Core:

?? https://6bit.dev/en/download/

---

# Check status
bin/sixbit-cli getblockchaininfo

Configuration file: `sixbit.conf`

Default locations:
- Linux: `~/.sixbit/sixbit.conf`
- macOS: `~/Library/Application Support/sixbit/sixbit.conf`
- Windows: `%APPDATA%\sixbit\sixbit.conf`


### Unix

Unpack the files into a directory and run:

- `bin/sixbit-qt` (GUI) or
- `bin/sixbitd` (headless)
- `bin/sixbit` (wrapper command)

The `sixbit` command supports subcommands like `sixbit gui`, `sixbit node`, and `sixbit rpc` exposing different functionality. Subcommands can be listed with `sixbit help`.

### Windows

Unpack the files into a directory, and then run sixbit-qt.exe.

### macOS

Drag Sixbit Core to your applications folder, and then run Sixbit Core.app.

### Need Help?

* See the documentation in the `doc/` folder.
* Open an issue on GitHub: https://github.com/sixbit-core/sixbit/issues
* Visit https://6bit.dev

Building
---------------------
The following are developer notes on how to build Sixbit Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows-msvc.md)
- [FreeBSD Build Notes](build-freebsd.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)

Development
---------------------
The sixbit repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://doxygen.6bit.dev/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)
- [Internal Design Docs](design/)

### Resources
* Discuss on the sixbit forums on discord etc.
* Discuss project-specific development on #sixbit-core-dev on Libera Chat. If you don't have an IRC client, you can use [web.libera.chat](https://web.libera.chat/#sixbit-core-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [sixbit.conf Configuration File](sixbit-conf.md)
- [CJDNS Support](cjdns.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [I2P Support](i2p.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [Managing Wallets](managing-wallets.md)
- [Multisig Tutorial](multisig-tutorial.md)
- [Offline Signing Tutorial](offline-signing-tutorial.md)
- [P2P bad ports definition and list](p2p-bad-ports.md)
- [PSBT support](psbt.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Transaction Relay Policy](policy/README.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
