# Copyright (c) 2019-present The Bitcoin Core developers
#!/bin/sh
# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/

#!/bin/sh
export LC_ALL=C

INPUT=$(cat)

if [ "${SIXBIT_VERIFY_COMMITS_ALLOW_SHA1:-0}" = 1 ]; then
    printf '%s\n' "$INPUT" | gpg --trust-model always "$@" 2>/dev/null
    exit $?
else
    VERSION_LINE="$(gpg --version | head -n1)"
    case "$VERSION_LINE" in
        "gpg (GnuPG) 1.4.1"*|"gpg (GnuPG) 2.0."*)
            echo "Please upgrade to at least gpg 2.1.10 to check for weak signatures" >&2
            printf '%s\n' "$INPUT" | gpg --trust-model always "$@" 2>/dev/null
            exit $?
            ;;
    esac

    printf '%s\n' "$INPUT" | gpg --trust-model always --weak-digest sha1 "$@" 2>/dev/null
    exit $?
fi
