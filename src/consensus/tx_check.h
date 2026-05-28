// Copyright (c) 2017-2019 The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_CONSENSUS_TX_CHECK_H
#define SIXBIT_CONSENSUS_TX_CHECK_H

/**
 * Context-independent transaction checking code that can be called outside the
 *.sixbit server and doesn't depend on chain or mempool state. Transaction
 * verification code that does call server functions or depend on server state
 * belongs in tx_verify.h/cpp instead.
 */

class CTransaction;
class TxValidationState;

bool CheckTransaction(const CTransaction& tx, TxValidationState& state);

#endif // SIXBIT_CONSENSUS_TX_CHECK_H
