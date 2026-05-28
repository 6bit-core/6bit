# Copyright (c) 2019-present The Bitcoin Core developers
#!/bin/sh
# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

export LC_ALL=C

if [ -n "$SOURCE_DATE_EPOCH" ]; then
  find . -exec touch -d "@$SOURCE_DATE_EPOCH" {} +
fi

find . | sort | "$1" -X@ "$2"
