# 6bit reproducible release notes

This setup uses Bitcoin Core's `depends` approach first because it is simpler and already exists in Bitcoin-derived trees.

Levels:

1. Practical reproducible-style builds:
   - Build pinned dependencies with `depends/`
   - Build from a clean Git tag
   - Produce SHA256SUMS
   - Sign SHA256SUMS

2. Stronger reproducible releases:
   - Port Bitcoin Core's Guix release flow to 6bit
   - Build `noncodesigned`
   - Apply detached Windows/macOS signatures
   - Build final `all`
   - Collect third-party attestations

Recommended release flow:

```bash
git clean -xfd
git checkout v1.0.0

./contrib/release/install-ubuntu-host.sh
VERSION=1.0.0 ./contrib/release/build-release.sh linux
VERSION=1.0.0 ./contrib/release/build-release.sh windows

cd dist
sha256sum *.tar.gz > SHA256SUMS
gpg --armor --detach-sign SHA256SUMS
```

For macOS, build on macOS first:

```bash
./contrib/release/install-macos-host.sh
VERSION=1.0.0 ./contrib/release/build-release.sh macos
```

Notes:
- Windows GUI cross-build requires `depends` Qt packages to be present and renamed cleanly.
- If your fork still has mixed target names, run:
  `cmake --build build-win64 --target help | grep -Ei "6bit|sixbit|bitcoin|qt"`
- Keep `ENABLE_IPC=OFF` until Cap'n Proto/libmultiprocess is fully stable in your release environment.
