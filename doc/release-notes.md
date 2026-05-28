# Sixbit Core v1.0.0 Release Notes

Sixbit Core version **v1.0.0** is now available:

?? https://6bit.dev/bin/sixbit-core-1.0.0/

This release includes new features, bug fixes, performance improvements, and updated translations.

---

## Reporting Issues

Please report bugs using the GitHub issue tracker:

?? https://github.com/6bit-core/6bit/issues

To receive security updates and announcements, consider subscribing to the sixbit mailing list (if available).

---

## How to Upgrade

If you are running an older version:

1. Shut down your node completely  
   (this may take a few minutes)

2. Upgrade depending on your platform:

- **Windows:** Run the installer  
- **macOS:** Replace `/Applications/sixbit-Qt.app`  
- **Linux:** Replace `sixbitd` / `sixbit-qt` binaries  

Upgrading from versions that have reached **End of Life (EOL)** is supported, but may take additional time if the data directory requires migration.

Older wallet versions remain compatible in most cases.

---

## Compatibility

Sixbit Core is tested on:

- Linux (Kernel 3.17+)  
- macOS 13+  
- Windows 10+  

It may also work on other Unix-like systems, but these are not regularly tested.

Running on unsupported systems is **not recommended**.

---

## Notable Changes

### Wallet

- #34156 wallet: fix unnamed legacy wallet migration failure  
- #34215 wallettool: fix `createfromdump` failure and walletsdir deletion  
- #34221 test: avoid backup name mismatch in migration tests  

---

### IPC

- #33511 init: fix Ctrl-C shutdown hangs during wait calls  

---

### Build

- #33950 guix: reduce allowed exported symbols  
- #34107 build: update minimum required Boost version  
- #34227 guix: fix `osslsigncode` tests  

---

### Tests

- #34137 test: remove hard `time.sleep(1)` in `feature_init.py`  
- #34226 wallet test: fix migration cleanup for relative wallets  

---

### Fuzzing

- #34091 fuzz: remove references to `address_deserialize_v2`  

---

### Documentation

- #34182 doc: update OpenBSD build guide  
- #34174 doc: update copyright year to 2026  

---

## Credits

Thanks to everyone who contributed to this release.

---

## License

Distributed under the MIT software license.
