// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_RANDOMENV_H
#define SIXBIT_RANDOMENV_H

#include <crypto/sha512.h>

/** Gather non-cryptographic environment data that changes over time. */
void RandAddDynamicEnv(CSHA512& hasher);

/** Gather non-cryptographic environment data that does not change over time. */
void RandAddStaticEnv(CSHA512& hasher);

#endif // SIXBIT_RANDOMENV_H
