// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <bench/bench.h>
#include <bench/data/block413567.raw.h>
#include <span.h>
#include <util/strencodings.h>

#include <vector>

static void HexStrBench(benchmark::Bench& bench)
{
    auto const& data = benchmark::data::block413567;
    bench.batch(data.size()).unit("byte").run([&] {
        auto hex = HexStr(data);
        ankerl::nanobench::doNotOptimizeAway(hex);
    });
}

BENCHMARK(HexStrBench, benchmark::PriorityLevel::HIGH);
