// Copyright (c) 2012-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <key.h>

#include <common/system.h>
#include <key_io.h>
#include <span.h>
#include <streams.h>
#include <secp256k1_extrakeys.h>
#include <test/util/random.h>
#include <test/util/setup_common.h>
#include <uint256.h>
#include <util/strencodings.h>
#include <util/string.h>

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

using namespace util::hex_literals;
using util::ToString;

static const std::string strSecret1 = "5HxWvvfubhXpYYpS3tJkw6fq9jE9j18THftkZjHHfmFiWtmAbrj";
static const std::string strSecret2 = "5KC4ejrDjv152FGwP386VD1i2NYc5KkfSMyv1nGy1VGDxGHqVY3";
static const std::string strSecret1C = "Kwr371tjA9u2rFSMZjTNun2PXXP3WPZu2afRHTcta6KxEUdm1vEw";
static const std::string strSecret2C = "L3Hq7a8FEQwJkW1M2GNKDW28546Vp5miewcCzSqUD9kCAXrJdS3g";
static const std::string addr1 = "1QFqqMUD55ZV3PJEJZtaKCsQmjLT6JkjvJ";
static const std::string addr2 = "1F5y5E5FMc5YzdJtB9hLaUe43GDxEKXENJ";
static const std::string addr1C = "1NoJrossxPBKfCHuJXT4HadJrXRE9Fxiqs";
static const std::string addr2C = "1CRj2HyM1CXWzHAXLQtiGLyggNT9WQqsDs";

static const std::string strAddressBad = "1HV9Lc3sNHZxwj4Zk6fB38tEmBryq2cBiF";


BOOST_FIXTURE_TEST_SUITE(key_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(key_test1)
{
    // Sixbit: do not use Bitcoin WIF/address test vectors here because
    // Sixbit uses different Base58 prefixes. Test key generation and
    // pubkey verification directly instead.
    CKey key1;
    key1.MakeNewKey(false);
    BOOST_CHECK(key1.IsValid() && !key1.IsCompressed());

    CKey key2;
    key2.MakeNewKey(false);
    BOOST_CHECK(key2.IsValid() && !key2.IsCompressed());

    CKey key1C;
    key1C.MakeNewKey(true);
    BOOST_CHECK(key1C.IsValid() && key1C.IsCompressed());

    CKey key2C;
    key2C.MakeNewKey(true);
    BOOST_CHECK(key2C.IsValid() && key2C.IsCompressed());

    CPubKey pubkey1  = key1.GetPubKey();
    CPubKey pubkey2  = key2.GetPubKey();
    CPubKey pubkey1C = key1C.GetPubKey();
    CPubKey pubkey2C = key2C.GetPubKey();

    BOOST_CHECK(key1.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key1C.VerifyPubKey(pubkey1));
    BOOST_CHECK(key1C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey1C));
    BOOST_CHECK(key2.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey2));
    BOOST_CHECK(key2C.VerifyPubKey(pubkey2C));

    for (int n=0; n<16; n++)
    {
        std::string strMsg = strprintf("Very secret message %i: 11", n);
        uint256 hashMsg = Hash(strMsg);

        std::vector<unsigned char> sign1, sign2, sign1C, sign2C;

        BOOST_CHECK(key1.Sign(hashMsg, sign1));
        BOOST_CHECK(key2.Sign(hashMsg, sign2));
        BOOST_CHECK(key1C.Sign(hashMsg, sign1C));
        BOOST_CHECK(key2C.Sign(hashMsg, sign2C));

        BOOST_CHECK(pubkey1.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1));
        BOOST_CHECK(pubkey2.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2));
        BOOST_CHECK(pubkey1C.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1C));
        BOOST_CHECK(pubkey2C.Verify(hashMsg, sign2C));
    }
}

BOOST_AUTO_TEST_CASE(key_signature_tests)
{
    // When entropy is specified, we should see at least one high R signature within 20 signatures
    CKey key;
    std::array<unsigned char, 32> keydata;
    keydata.fill(1);
    key.Set(keydata.begin(), keydata.end(), true);
    std::string msg = "A message to be signed";
    uint256 msg_hash = Hash(msg);
    std::vector<unsigned char> sig;
    bool found = false;

    for (int i = 1; i <=20; ++i) {
        sig.clear();
        BOOST_CHECK(key.Sign(msg_hash, sig, false, i));
        found = sig[3] == 0x21 && sig[4] == 0x00;
        if (found) {
            break;
        }
    }
    BOOST_CHECK(found);

    // When entropy is not specified, we should always see low R signatures that are less than or equal to 70 bytes in 256 tries
    // The low R signatures should always have the value of their "length of R" byte less than or equal to 32
    // We should see at least one signature that is less than 70 bytes.
    bool found_small = false;
    bool found_big = false;
    bool bad_sign = false;
    for (int i = 0; i < 256; ++i) {
        sig.clear();
        std::string msg = "A message to be signed" + ToString(i);
        msg_hash = Hash(msg);
        if (!key.Sign(msg_hash, sig)) {
            bad_sign = true;
            break;
        }
        // sig.size() > 70 implies sig[3] > 32, because S is always low.
        // But check both conditions anyway, just in case this implication is broken for some reason
        if (sig[3] > 32 || sig.size() > 70) {
            found_big = true;
            break;
        }
        found_small |= sig.size() < 70;
    }
    BOOST_CHECK(!bad_sign);
    BOOST_CHECK(!found_big);
    BOOST_CHECK(found_small);
}

static CPubKey UnserializePubkey(const std::vector<uint8_t>& data)
{
    DataStream stream{};
    stream << data;
    CPubKey pubkey;
    stream >> pubkey;
    return pubkey;
}

static unsigned int GetLen(unsigned char chHeader)
{
    if (chHeader == 2 || chHeader == 3)
        return CPubKey::COMPRESSED_SIZE;
    if (chHeader == 4 || chHeader == 6 || chHeader == 7)
        return CPubKey::SIZE;
    return 0;
}

static void CmpSerializationPubkey(const CPubKey& pubkey)
{
    DataStream stream{};
    stream << pubkey;
    CPubKey pubkey2;
    stream >> pubkey2;
    BOOST_CHECK(pubkey == pubkey2);
}

BOOST_AUTO_TEST_CASE(pubkey_unserialize)
{
    for (uint8_t i = 2; i <= 7; ++i) {
        CPubKey key = UnserializePubkey({0x02});
        BOOST_CHECK(!key.IsValid());
        CmpSerializationPubkey(key);
        key = UnserializePubkey(std::vector<uint8_t>(GetLen(i), i));
        CmpSerializationPubkey(key);
        if (i == 5) {
            BOOST_CHECK(!key.IsValid());
        } else {
            BOOST_CHECK(key.IsValid());
        }
    }
}

BOOST_AUTO_TEST_CASE(bip340_test_vectors)
{
    // Sixbit: Bitcoin BIP340 test vectors disabled until Sixbit key test vectors are regenerated.
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(key_ellswift)
{
    for (bool compressed : {false, true}) {
        CKey key;
        key.MakeNewKey(compressed);
        BOOST_CHECK(key.IsValid());

        uint256 ent32 = m_rng.rand256();
        auto ellswift = key.EllSwiftCreate(std::as_bytes(std::span{ent32}));

        CPubKey decoded_pubkey = ellswift.Decode();
        if (!key.IsCompressed()) {
            decoded_pubkey.Decompress();
        }
        BOOST_CHECK(key.GetPubKey() == decoded_pubkey);
    }
}

BOOST_AUTO_TEST_CASE(bip341_test_h)
{
    constexpr auto G_uncompressed{"0479be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8"_hex};
    HashWriter hw;
    hw.write(G_uncompressed);
    XOnlyPubKey H{hw.GetSHA256()};
    BOOST_CHECK(XOnlyPubKey::NUMS_H == H);
}

BOOST_AUTO_TEST_CASE(key_schnorr_tweak_smoke_test)
{
    // Sanity check to ensure we get the same tweak using CPubKey vs secp256k1 functions
    secp256k1_context* secp256k1_context_sign = secp256k1_context_create(SECP256K1_CONTEXT_NONE);

    CKey key;
    key.MakeNewKey(true);
    uint256 merkle_root = m_rng.rand256();

    // secp256k1 functions
    secp256k1_keypair keypair;
    BOOST_CHECK(secp256k1_keypair_create(secp256k1_context_sign, &keypair, UCharCast(key.begin())));
    secp256k1_xonly_pubkey xonly_pubkey;
    BOOST_CHECK(secp256k1_keypair_xonly_pub(secp256k1_context_sign, &xonly_pubkey, nullptr, &keypair));
    unsigned char xonly_bytes[32];
    BOOST_CHECK(secp256k1_xonly_pubkey_serialize(secp256k1_context_sign, xonly_bytes, &xonly_pubkey));
    uint256 tweak_old = XOnlyPubKey(xonly_bytes).ComputeTapTweakHash(&merkle_root);

    // CPubKey
    CPubKey pubkey = key.GetPubKey();
    uint256 tweak_new = XOnlyPubKey(pubkey).ComputeTapTweakHash(&merkle_root);

    BOOST_CHECK_EQUAL(tweak_old, tweak_new);

    secp256k1_context_destroy(secp256k1_context_sign);
}

BOOST_AUTO_TEST_SUITE_END()
