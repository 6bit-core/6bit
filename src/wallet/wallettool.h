// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2016-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_WALLET_WALLETTOOL_H
#define SIXBIT_WALLET_WALLETTOOL_H

#include <string>

class ArgsManager;

namespace wallet {
namespace WalletTool {

bool ExecuteWalletToolFunc(const ArgsManager& args, const std::string& command);

} // namespace WalletTool
} // namespace wallet

#endif // SIXBIT_WALLET_WALLETTOOL_H
