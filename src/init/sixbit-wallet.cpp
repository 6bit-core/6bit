// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2021-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <interfaces/init.h>

#include <memory>

namespace interfaces {
std::unique_ptr<Init> MakeWalletInit(int argc, char* argv[], int& exit_status)
{
    return std::make_unique<Init>();
}
} // namespace interfaces
