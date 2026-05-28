// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_TEST_FUZZ_UTIL_CHECK_GLOBALS_H
#define SIXBIT_TEST_FUZZ_UTIL_CHECK_GLOBALS_H

#include <atomic>
#include <memory>
#include <optional>
#include <string>

extern std::atomic<bool> g_used_system_time;

struct CheckGlobalsImpl;
struct CheckGlobals {
    CheckGlobals();
    ~CheckGlobals();
    std::unique_ptr<CheckGlobalsImpl> m_impl;
};

#endif // SIXBIT_TEST_FUZZ_UTIL_CHECK_GLOBALS_H
