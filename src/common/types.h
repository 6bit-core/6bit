// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2010-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

//! @file common/types.h is a home for simple enum and struct type definitions
//! that can be used internally by functions in the libsixbit_common library,
//! but also used externally by node, wallet, and GUI code.
//!
//! This file is intended to define only simple types that do not have external
//! dependencies. More complicated types should be defined in dedicated header
//! files.

#ifndef SIXBIT_COMMON_TYPES_H
#define SIXBIT_COMMON_TYPES_H

namespace common {
enum class PSBTError {
    MISSING_INPUTS,
    SIGHASH_MISMATCH,
    EXTERNAL_SIGNER_NOT_FOUND,
    EXTERNAL_SIGNER_FAILED,
    UNSUPPORTED,
    INCOMPLETE,
    OK,
};
} // namespace common

#endif // SIXBIT_COMMON_TYPES_H
