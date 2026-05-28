// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_WALLET_LOAD_H
#define SIXBIT_WALLET_LOAD_H

#include <string>
#include <vector>

class ArgsManager;
class CScheduler;

namespace interfaces {
class Chain;
} // namespace interfaces

namespace wallet {
struct WalletContext;

//! Responsible for reading and validating the -wallet arguments and verifying the wallet database.
bool VerifyWallets(WalletContext& context);

//! Load wallet databases.
bool LoadWallets(WalletContext& context);

//! Complete startup of wallets.
void StartWallets(WalletContext& context);

void UnloadWallets(WalletContext& context);
} // namespace wallet

#endif // SIXBIT_WALLET_LOAD_H
