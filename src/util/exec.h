// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_UTIL_EXEC_H
#define SIXBIT_UTIL_EXEC_H

#include <util/fs.h>

#include <string_view>

namespace util {
//! Cross-platform wrapper for POSIX execvp function.
//! Arguments and return value are the same as for POSIX execvp, and the argv
//! array should consist of null terminated strings and be null terminated
//! itself, like the POSIX function.
int ExecVp(const char* file, char* const argv[]);
//! Return path to current executable assuming it was invoked with argv0.
//! If path could not be determined, returns an empty path.
fs::path GetExePath(std::string_view argv0);
} // namespace util

#endif // SIXBIT_UTIL_EXEC_H
