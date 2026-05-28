// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2021-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

//! @file
//! @brief Common init functions shared by sixbit-node, sixbit-wallet, etc.

#ifndef SIXBIT_INIT_COMMON_H
#define SIXBIT_INIT_COMMON_H

#include <util/result.h>

class ArgsManager;

namespace init {
void AddLoggingArgs(ArgsManager& args);
void SetLoggingOptions(const ArgsManager& args);
[[nodiscard]] util::Result<void> SetLoggingCategories(const ArgsManager& args);
[[nodiscard]] util::Result<void> SetLoggingLevel(const ArgsManager& args);
bool StartLogging(const ArgsManager& args);
void LogPackageVersion();
} // namespace init

#endif // SIXBIT_INIT_COMMON_H
