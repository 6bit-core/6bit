### Verify Binaries

#### Preparation

Releases are signed by a number of public keys listed in the sixbit signatures
repository. When verifying binary downloads, you decide which of these public
keys you trust and then use that trust model to evaluate the signature on a
file containing hashes of the release binaries. The downloaded binaries are
then hashed and compared to the signed checksum file.

First, decide which public keys you want to trust. For each key, import it into
your local GPG installation.

You can obtain these keys by:
- using a browser with a key server such as `keyserver.ubuntu.com`,
- running `gpg --keyserver <url> --recv-keys <key>`, or
- using the packaged `verify.py --import-keys ...` script to retrieve
  unrecognized keys automatically.

#### Usage

This script attempts to download the checksum file (`SHA256SUMS`) and the
corresponding signature file (`SHA256SUMS.asc`) from `https://6bit.dev`.

It first checks whether the checksum file is valid based on a plurality of
signatures, then downloads the release files specified in the checksum file and
verifies that their hashes match the signed checksums.

If unrecognized pubkeys appear in the signature file, the script can prompt the
user to download them. To enable this behavior, use the `--import-keys` flag.

The script returns 0 if all checks pass. It returns 1 if either the signature
check or the hash check fails. An exit code greater than 1 indicates an error.

See the `Config` object for various options.

#### Examples

Validate releases with default settings:

```sh
./contrib/verify-binaries/verify.py pub 1.0.0
./contrib/verify-binaries/verify.py pub 1.0.0-rc1

```

Get JSON output and don't prompt for user input (no auto key import):

```sh
./contrib/verify-binaries/verify.py --json pub 1.0.0-x86_64-linux
./contrib/verify-binaries/verify.py --json pub 1.0.0-rc1-win64-setup.exe
```

Rely only on local GPG state and manually specified keys, while requiring a
threshold of at least 2 trusted signatures:
```sh
./contrib/verify-binaries/verify.py \
    --trusted-keys KEY1,KEY2 \
    --min-good-sigs 2 pub 1.0.0-linux
```

If you only want to download the binaries for a certain architecture and/or platform, add the corresponding suffix, e.g.:

```sh
./contrib/verify-binaries/verify.py pub 1.0.0-x86_64-linux
./contrib/verify-binaries/verify.py pub 1.0.0-darwin
./contrib/verify-binaries/verify.py pub 1.0.0-win64-setup.exe
```

If you do not want to keep the downloaded binaries, specify the cleanup option.

```sh
./contrib/verify-binaries/verify.py pub --cleanup 1.0.0
```

Use the bin subcommand to verify all files listed in a local checksum file

```sh
./contrib/verify-binaries/verify.py bin SHA256SUMS
```

Verify only a subset of the files listed in a local checksum file

```sh
./contrib/verify-binaries/verify.py bin ~/Downloads/SHA256SUMS \
    ~/Downloads/sixbit-1.0.0-x86_64-linux-gnu.tar.gz \
    ~/Downloads/sixbit-1.0.0-arm-linux-gnueabihf.tar.gz
```
