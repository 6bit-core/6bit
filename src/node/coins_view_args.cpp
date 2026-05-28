// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <node/coins_view_args.h>

#include <common/args.h>
#include <txdb.h>

namespace node {
void ReadCoinsViewArgs(const ArgsManager& args, CoinsViewOptions& options)
{
    if (auto value = args.GetIntArg("-dbbatchsize")) options.batch_write_bytes = *value;
    if (auto value = args.GetIntArg("-dbcrashratio")) options.simulate_crash_ratio = *value;
}
} // namespace node
