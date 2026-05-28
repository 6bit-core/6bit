// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_UTIL_OVERLOADED_H
#define SIXBIT_UTIL_OVERLOADED_H

namespace util {
//! Overloaded helper for std::visit. This helper and std::visit in general are
//! useful to write code that switches on a variant type. Unlike if/else-if and
//! switch/case statements, std::visit will trigger compile errors if there are
//! unhandled cases.
//!
//! Implementation comes from and example usage can be found at
//! https://en.cppreference.com/w/cpp/utility/variant/visit#Example
template<class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };

//! Explicit deduction guide (not needed after clang-17)
template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;
} // namespace util

#endif // SIXBIT_UTIL_OVERLOADED_H
