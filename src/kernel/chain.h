// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_KERNEL_CHAIN_H
#define SIXBIT_KERNEL_CHAIN_H

#include<iostream>

class CBlock;
class CBlockIndex;
namespace interfaces {
struct BlockInfo;
} // namespace interfaces

namespace kernel {
//! Return data from block index.
interfaces::BlockInfo MakeBlockInfo(const CBlockIndex* block_index, const CBlock* data = nullptr);

} // namespace kernel

//! This enum describes the various roles a specific Chainstate instance can take.
//! Other parts of the system sometimes need to vary in behavior depending on the
//! existence of a background validation chainstate, e.g. when building indexes.
enum class ChainstateRole {
    // Single chainstate in use, "normal" IBD mode.
    NORMAL,

    // Doing IBD-style validation in the background. Implies use of an assumed-valid
    // chainstate.
    BACKGROUND,

    // Active assumed-valid chainstate. Implies use of a background IBD chainstate.
    ASSUMEDVALID,
};

std::ostream& operator<<(std::ostream& os, const ChainstateRole& role);

#endif // SIXBIT_KERNEL_CHAIN_H
