// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_HEADERSSYNC_H
#define SIXBIT_HEADERSSYNC_H

#include <arith_uint256.h>
#include <chain.h>
#include <consensus/params.h>
#include <net.h>
#include <primitives/block.h>
#include <uint256.h>
#include <util/bitdeque.h>
#include <util/hasher.h>

#include <deque>
#include <vector>

// A compressed CBlockHeader, which leaves out the prevhash
struct CompressedHeader {
    // header
    int32_t nVersion{0};
    uint256 hashMerkleRoot;
    uint32_t nTime{0};
    uint32_t nBits{0};
    uint32_t nNonce{0};

    CompressedHeader()
    {
        hashMerkleRoot.SetNull();
    }

    CompressedHeader(const CBlockHeader& header)
    {
        nVersion = header.nVersion;
        hashMerkleRoot = header.hashMerkleRoot;
        nTime = header.nTime;
        nBits = header.nBits;
        nNonce = header.nNonce;
    }

    CBlockHeader GetFullHeader(const uint256& hash_prev_block) {
        CBlockHeader ret;
        ret.nVersion = nVersion;
        ret.hashPrevBlock = hash_prev_block;
        ret.hashMerkleRoot = hashMerkleRoot;
        ret.nTime = nTime;
        ret.nBits = nBits;
        ret.nNonce = nNonce;
        return ret;
    };
};


class HeadersSyncState {
public:
    ~HeadersSyncState() = default;

    enum class State {
        /** PRESYNC means the peer has not yet demonstrated their chain has
         * sufficient work and we're only building commitments to the chain they
         * serve us. */
        PRESYNC,
        /** REDOWNLOAD means the peer has given us a high-enough-work chain,
         * and now we're redownloading the headers we saw before and trying to
         * accept them */
        REDOWNLOAD,
        /** We're done syncing with this peer and can discard any remaining state */
        FINAL
    };

    /** Return the current state of our download */
    State GetState() const { return m_download_state; }

    /** Return the height reached during the PRESYNC phase */
    int64_t GetPresyncHeight() const { return m_current_height; }

    /** Return the block timestamp of the last header received during the PRESYNC phase. */
    uint32_t GetPresyncTime() const { return m_last_header_received.nTime; }

    /** Return the amount of work in the chain received during the PRESYNC phase. */
    arith_uint256 GetPresyncWork() const { return m_current_chain_work; }

    /** Construct a HeadersSyncState object representing a headers sync via this
     *  download-twice mechanism).
     *
     * id: node id (for logging)
     * consensus_params: parameters needed for difficulty adjustment validation
     * chain_start: best known fork point that the peer's headers branch from
     * minimum_required_work: amount of chain work required to accept the chain
     */
    HeadersSyncState(NodeId id, const Consensus::Params& consensus_params,
            const CBlockIndex* chain_start, const arith_uint256& minimum_required_work);

    /** Result data structure for ProcessNextHeaders. */
    struct ProcessingResult {
        std::vector<CBlockHeader> pow_validated_headers;
        bool success{false};
        bool request_more{false};
    };

    /** Process a batch of headers, once a sync via this mechanism has started
     *
     * received_headers: headers that were received over the network for processing.
     *                   Assumes the caller has already verified the headers
     *                   are continuous, and has checked that each header
     *                   satisfies the proof-of-work target included in the
     *                   header (but not necessarily verified that the
     *                   proof-of-work target is correct and passes consensus
     *                   rules).
     * full_headers_message: true if the message was at max capacity,
     *                       indicating more headers may be available
     * ProcessingResult.pow_validated_headers: will be filled in with any
     *                       headers that the caller can fully process and
     *                       validate now (because these returned headers are
     *                       on a chain with sufficient work)
     * ProcessingResult.success: set to false if an error is detected and the sync is
     *                       aborted; true otherwise.
     * ProcessingResult.request_more: if true, the caller is suggested to call
     *                       NextHeadersRequestLocator and send a getheaders message using it.
     */
    ProcessingResult ProcessNextHeaders(const std::vector<CBlockHeader>&
            received_headers, bool full_headers_message);

    /** Issue the next GETHEADERS message to our peer.
     *
     * This will return a locator appropriate for the current sync object, to continue the
     * synchronization phase it is in.
     */
    CBlockLocator NextHeadersRequestLocator() const;

protected:
    /** The (secret) offset on the heights for which to create commitments.
     *
     * m_header_commitments entries are created at any height h for which
     * (h % HEADER_COMMITMENT_PERIOD) == m_commit_offset. */
    const unsigned m_commit_offset;

private:
    /** Clear out all download state that might be in progress (freeing any used
     * memory), and mark this object as no longer usable.
     */
    void Finalize();

    /**
     *  Only called in PRESYNC.
     *  Validate the work on the headers we received from the network, and
     *  store commitments for later. Update overall state with successfully
     *  processed headers.
     *  On failure, this invokes Finalize() and returns false.
     */
    bool ValidateAndStoreHeadersCommitments(const std::vector<CBlockHeader>& headers);

    /** In PRESYNC, process and update state for a single header */
    bool ValidateAndProcessSingleHeader(const CBlockHeader& current);

    /** In REDOWNLOAD, check a header's commitment (if applicable) and add to
     * buffer for later processing */
    bool ValidateAndStoreRedownloadedHeader(const CBlockHeader& header);

    /** Return a set of headers that satisfy our proof-of-work threshold */
    std::vector<CBlockHeader> PopHeadersReadyForAcceptance();

private:
    /** NodeId of the peer (used for log messages) **/
    const NodeId m_id;

    /** We use the consensus params in our anti-DoS calculations */
    const Consensus::Params& m_consensus_params;

    /** Store the last block in our block index that the peer's chain builds from */
    const CBlockIndex* m_chain_start{nullptr};

    /** Minimum work that we're looking for on this chain. */
    const arith_uint256 m_minimum_required_work;

    /** Work that we've seen so far on the peer's chain */
    arith_uint256 m_current_chain_work;

    /** m_hasher is a salted hasher for making our 1-bit commitments to headers we've seen. */
    const SaltedUint256Hasher m_hasher;

    /** A queue of commitment bits, created during the 1st phase, and verified during the 2nd. */
    bitdeque<> m_header_commitments;

    /** m_max_commitments is a bound we calculate on how long an honest peer's chain could be,
     * given the MTP rule.
     *
     * Any peer giving us more headers than this will have its sync aborted. This serves as a
     * memory bound on m_header_commitments. */
    uint64_t m_max_commitments{0};

    /** Store the latest header received while in PRESYNC (initialized to m_chain_start) */
    CBlockHeader m_last_header_received;

    /** Height of m_last_header_received */
    int64_t m_current_height{0};

    /** During phase 2 (REDOWNLOAD), we buffer redownloaded headers in memory
     *  until enough commitments have been verified; those are stored in
     *  m_redownloaded_headers */
    std::deque<CompressedHeader> m_redownloaded_headers;

    /** Height of last header in m_redownloaded_headers */
    int64_t m_redownload_buffer_last_height{0};

    /** Hash of last header in m_redownloaded_headers (initialized to
     * m_chain_start). We have to cache it because we don't have hashPrevBlock
     * available in a CompressedHeader.
     */
    uint256 m_redownload_buffer_last_hash;

    /** The hashPrevBlock entry for the first header in m_redownloaded_headers
     * We need this to reconstruct the full header when it's time for
     * processing.
     */
    uint256 m_redownload_buffer_first_prev_hash;

    /** The accumulated work on the redownloaded chain. */
    arith_uint256 m_redownload_chain_work;

    /** Set this to true once we encounter the target blockheader during phase
     * 2 (REDOWNLOAD). At this point, we can process and store all remaining
     * headers still in m_redownloaded_headers.
     */
    bool m_process_all_remaining_headers{false};

    /** Current state of our headers sync. */
    State m_download_state{State::PRESYNC};
};

#endif // SIXBIT_HEADERSSYNC_H
