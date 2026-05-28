# Copyright (c) 2019-present The Bitcoin Core developers
#!/usr/bin/env bash
#
# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

export LC_ALL=C.UTF-8

set -o errexit; source ./ci/test/00_setup_env.sh
set -o errexit
"./ci/test/02_run_container.py"
