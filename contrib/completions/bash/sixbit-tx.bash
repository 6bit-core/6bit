# bash programmable completion for sixbit-tx(1)
# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/

_sixbit_tx() {
    local cur prev words=() cword
    local sixbit_tx

    COMPREPLY=()
    _get_comp_words_by_ref -n =: cur prev words cword

    sixbit_tx="$(command -v "${words[0]}")"
    [ -x "$sixbit_tx" ] || return 0

    case "$cur" in
        load=*:*)
            cur="${cur#load=*:}"
            _filedir
            return 0
            ;;
        *=*)
            return 0
            ;;
    esac

    if [[ "$cword" == 1 || ( "$prev" != "-create" && "$prev" == -* ) ]]; then
        local helpopts
        helpopts=$("$sixbit_tx" -help | sed -e '/^  -/ p' -e d )
        COMPREPLY=( $( compgen -W "$helpopts" -- "$cur" ) )
    else
        local helpcmds
        helpcmds=$("$sixbit_tx" -help | sed -e '1,/Commands:/d' -e 's/=.*/=/' -e '/^  [a-z]/ p' -e d )
        COMPREPLY=( $( compgen -W "$helpcmds" -- "$cur" ) )
    fi

    if [[ "${COMPREPLY[*]}" == *= ]]; then
        compopt -o nospace
    fi

    return 0
} &&
complete -F _sixbit_tx sixbit-tx