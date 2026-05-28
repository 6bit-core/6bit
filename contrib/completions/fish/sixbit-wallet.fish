# Disable files from being included in completions by default
complete --command sixbit-wallet --no-files

# Extract options
function __fish_sixbit_wallet_get_options
    set --local cmd (commandline -opc)[1]
    for option in ($cmd -help 2>&1 | string match -r '^  -.*' | string replace -r '  -' '-' | string replace -r '=.*' '=')
        echo $option
    end
end

# Extract commands
function __fish_sixbit_wallet_get_commands
    argparse 'commandsonly' -- $argv
    set --local cmd (commandline -opc)[1]
    set --local commands

    if set -q _flag_commandsonly
        set --append commands ($cmd -help 2>/dev/null | sed -e '1,/Commands:/d' -e 's/=/=\t/' -e 's/(=/=/' -e '/^  [a-z]/ p' -e d | string replace -r '\ \ ' '' | string replace -r '=.*' '')
    else
        set --append commands ($cmd -help 2>/dev/null | sed -e '1,/Commands:/d' -e 's/=/=\t/' -e 's/(=/=/' -e '/^  [a-z]/ p' -e d | string replace -r '\ \ ' '')
    end

    for command in $commands
        echo $command
    end
end

# Add options
complete \
    --command sixbit-wallet \
    --condition "not __fish_seen_subcommand_from (__fish_sixbit_wallet_get_commands --commandsonly)"\
    --arguments "(__fish_sixbit_wallet_get_options)"

# Add commands
complete \
    --command sixbit-wallet \
    --condition "not __fish_seen_subcommand_from (__fish_sixbit_wallet_get_commands)" \
    --arguments "(__fish_sixbit_wallet_get_commands)"

# Add file completions for load and set commands
complete --command sixbit-wallet \
    --condition "string match -r -- '(dumpfile|datadir)=' (commandline -pt)" \
    --force-files