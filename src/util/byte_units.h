// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_UTIL_BYTE_UNITS_H
#define SIXBIT_UTIL_BYTE_UNITS_H

#include <util/overflow.h>

#include <stdexcept>

//! Overflow-safe conversion of MiB to bytes.
constexpr size_t operator""_MiB(unsigned long long mebibytes)
{
    auto bytes{CheckedLeftShift(mebibytes, 20)};
    if (!bytes || *bytes > std::numeric_limits<size_t>::max()) {
        throw std::overflow_error("MiB value too large for size_t byte conversion");
    }
    return *bytes;
}

#endif // SIXBIT_UTIL_BYTE_UNITS_H
