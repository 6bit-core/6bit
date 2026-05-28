// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <bench/bench.h>
#include <test/util/setup_common.h>
#include <validation.h>

#include <memory>

static void CheckBlockIndex(benchmark::Bench& bench)
{
    auto testing_setup{MakeNoLogFileContext<TestChain100Setup>()};
    // Mine some more blocks
    testing_setup->mineBlocks(1000);
    bench.run([&] {
        testing_setup->m_node.chainman->CheckBlockIndex();
    });
}


BENCHMARK(CheckBlockIndex, benchmark::PriorityLevel::HIGH);
