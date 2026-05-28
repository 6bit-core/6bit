Sixbit Core
=========

https://6bit.dev

For an immediately usable binary release of Sixbit Core, see
https://6bit.dev/en/download/.

What is Sixbit Core?
------------------

Sixbit Core connects to the sixbit peer-to-peer network to download and fully
validate blocks and transactions. It also includes a wallet and graphical user
interface, which can be built optionally.

Further information about Sixbit Core is available in the [doc directory](/doc).

License
-------

Sixbit Core is released under the terms of the MIT license. See [COPYING](COPYING)
or https://opensource.org/license/MIT for details.

Sixbit Core (also referred to as 6bit Core) is a fork of the Bitcoin Core project
and is derived from the open-source work of the global Bitcoin developer community.

This project gratefully acknowledges and gives full credit to all past, present, 
and future contributors to Bitcoin. The original design, implementation, and ongoing 
development of Bitcoin are the result of the collective efforts of many individuals, 
beginning with Satoshi Nakamoto and continuing through the Bitcoin Core development 
community and other contributors worldwide.

Sixbit Core does not claim ownership of the original Bitcoin codebase. All original 
work remains subject to its respective licenses, including the MIT License under which 
Bitcoin Core is distributed.

Any modifications, branding changes, or additional features introduced in 6bit Core 
are the responsibility of this project are not intended in any way to minimize, 
replace or erase credit attributable to Bitcoin Core developers.

This project exists as an independent initiative inspired by Bitcoin’s principles and 
is not affiliated with or endorsed by the Bitcoin Core project or its contributors.


Development Process
-------------------

The `master` branch is regularly built (see `doc/build-*.md` for instructions)
and tested, but it is not guaranteed to be completely stable. Stable release
versions of Sixbit Core are identified by
[tags](https://github.com/6bit-core/6bit/tags), which are created from release
branches.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md),
and useful hints for developers can be found in
[doc/developer-notes.md](doc/developer-notes.md).

Testing
-------

Testing and code review are the bottleneck for development. We often receive
more pull requests than can be reviewed and tested on short notice. Please be
patient, and help by testing other people's pull requests. Remember that this
is a security-critical project where mistakes can cost people money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md)
for new code and to add tests for older code where appropriate. Unit tests can
be compiled and run with `ctest`, assuming they were not disabled when the
build system was generated. Further details on running and extending unit tests
can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written in Python.
These tests can be run, if the [test dependencies](/test) are installed, with
`build/test/functional/test_runner.py` (assuming `build` is your build
directory).

The CI systems make sure that every pull request is tested on Windows, Linux,
and macOS. CI should pass on all commits before merge to avoid unrelated CI
failures affecting new pull requests.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description when testing the changes is
not straightforward.
