# bash programmable completion for sixbitd(1) and sixbit-qt(1)
# Copyright (c) 2012-2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/

_sixbitd() {
    local cur prev words=() cword
    local sixbitd

    # save and use original argument to invoke sixbitd for -help
    # it might not be in $PATH

    COMPREPLY=()
    _get_comp_words_by_ref -n = cur prev words cword
	sixbitd="$(command -v "${words[0]}")"
	[ -x "$sixbitd" ] || return 0

    case "$cur" in
        -conf=*|-pid=*|-loadblock=*|-rpccookiefile=*|-wallet=*)
            cur="${cur#*=}"
            _filedir
            return 0
            ;;
        -datadir=*)
            cur="${cur#*=}"
            _filedir -d
            return 0
            ;;
        -*=*)	# prevent nonsense completions
            return 0
            ;;
        *)

            # only parse -help if sensible
            if [[ -z "$cur" || "$cur" =~ ^- ]]; then
                local helpopts
                helpopts=$("$sixbitd" -help 2>&1 | awk '$1 ~ /^-/ { sub(/=.*/, "="); print $1 }')
                COMPREPLY=( $( compgen -W "$helpopts" -- "$cur" ) )
            fi

            # Prevent space if an argument is desired
            if [[ "${COMPREPLY[*]}" == *= ]]; then
                compopt -o nospace
            fi
            return 0
            ;;
    esac
} &&
complete -F _sixbitd sixbitd sixbit-qt

# Local variables:
# mode: shell-script
# sh-basic-offset: 4
# sh-indent-comment: t
# indent-tabs-mode: nil
# End:
# ex: ts=4 sw=4 et filetype=sh
