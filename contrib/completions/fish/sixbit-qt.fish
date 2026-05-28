# Disable files from being included in completions by default
complete --command sixbit-qt --no-files

function __fish_sixbitqt_get_options
    argparse 'nofiles' -- $argv
    set --local cmd (commandline -opc)[1]
    set --local options

    if set -q _flag_nofiles
        set --append options ($cmd -help-debug 2>/dev/null | string match -r '^  -.*' | string replace -r '  -' '-' | string replace -r '=.*' '=' | string match --invert -r '^.*=$')
    else
        set --append options ($cmd -help-debug 2>/dev/null | string match -r '^  -.*' | string replace -r '  -' '-' | string replace -r '=.*' '=' | string match -r '^.*=$')
    end

    for option in $options
        echo $option
    end
end

# Add options that may take file-like values
complete \
    --command sixbit-qt \
    --no-files \
    --arguments "(__fish_sixbitqt_get_options)"

# Enable file completions only when the token looks like *=
complete \
    --command sixbit-qt \
    --condition 'string match --regex -- ".*=" (commandline -pt)' \
    --force-files

# Add non-file options
complete \
    --command sixbit-qt \
    --no-files \
    --arguments "(__fish_sixbitqt_get_options --nofiles)"