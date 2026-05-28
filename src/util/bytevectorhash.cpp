// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <crypto/siphash.h>
#include <random.h>
#include <util/bytevectorhash.h>

#include <vector>

ByteVectorHash::ByteVectorHash() :
    m_k0(FastRandomContext().rand64()),
    m_k1(FastRandomContext().rand64())
{
}

size_t ByteVectorHash::operator()(const std::vector<unsigned char>& input) const
{
    return CSipHasher(m_k0, m_k1).Write(input).Finalize();
}
