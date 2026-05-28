// Copyright (c) 2014-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_CRYPTO_SHA512_H
#define SIXBIT_CRYPTO_SHA512_H

#include <cstdint>
#include <cstdlib>

/** A hasher class for SHA-512. */
class CSHA512
{
private:
    uint64_t s[8];
    unsigned char buf[128];
    uint64_t bytes{0};

public:
    static constexpr size_t OUTPUT_SIZE = 64;

    CSHA512();
    CSHA512& Write(const unsigned char* data, size_t len);
    void Finalize(unsigned char hash[OUTPUT_SIZE]);
    CSHA512& Reset();
    uint64_t Size() const { return bytes; }
};

#endif // SIXBIT_CRYPTO_SHA512_H
