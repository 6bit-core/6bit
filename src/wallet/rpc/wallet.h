// Copyright (c) 2016-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_WALLET_RPC_WALLET_H
#define SIXBIT_WALLET_RPC_WALLET_H

#include <span.h>

class CRPCCommand;

namespace wallet {
std::span<const CRPCCommand> GetWalletRPCCommands();
} // namespace wallet

#endif // SIXBIT_WALLET_RPC_WALLET_H
