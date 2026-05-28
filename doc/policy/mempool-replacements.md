# Mempool Replacements

## Current Replace-by-Fee Policy

A transaction conflicts with an in-mempool transaction (a *directly conflicting transaction*) if it spends one or more of the same inputs. A transaction may conflict with multiple in-mempool transactions.

A transaction (the *replacement transaction*) may replace its directly conflicting transactions and their in-mempool descendants (together, the *original transactions*) if—*in addition to satisfying all other consensus and policy rules*—each of the following conditions is met:

1. *(Removed)*

2. The replacement transaction may only include an unconfirmed input if that input was also included in one of the directly conflicting transactions.  
   An *unconfirmed input* is one that spends an output from a currently unconfirmed transaction.

   *Rationale*: When Replace-by-Fee (RBF) was originally implemented, the mempool did not track ancestor feerates. This rule was introduced as a temporary restriction.

3. The replacement transaction must pay an absolute fee at least equal to the sum of the fees paid by the original transactions.

   *Rationale*: Requiring only a higher feerate could allow an attacker to bypass minimum relay feerate requirements by repeatedly submitting slightly smaller replacements without increasing total fees. Additionally, if any original transaction would be included in the next block by a rational miner, allowing a replacement that reduces total fees would be economically inconsistent.

4. The additional fee paid by the replacement transaction (i.e., the difference between its fee and the sum of the original transactions' fees) must cover its bandwidth cost at or above the node’s *incremental relay feerate*.

   Example:  
   If the incremental relay feerate is `0.1 sat/vB` and the replacement transaction is `500 vB`, the replacement must pay at least `50 satoshis` more than the originals.

   *Rationale*: Prevents DoS attacks where an attacker repeatedly replaces transactions while paying only negligible additional fees (e.g., 1 satoshi each time).

5. The total number of original transactions must not exceed 100.

   More precisely, the sum of the descendant counts (each transaction plus all of its descendants) for all directly conflicting transactions must not exceed 100. This may overestimate the actual number of affected transactions.

   *Rationale*: Prevents DoS attacks where large portions of the mempool are repeatedly replaced using transactions with extensive descendant trees.

6. The replacement transaction’s feerate must be strictly greater than the feerate of each directly conflicting transaction.

   *Rationale*: Originally intended to ensure that the replacement transaction is more attractive for block inclusion than the transactions it replaces. This rule predates ancestor feerate-based transaction selection.

---

## Notes

- These rules are similar to, but not identical with, BIP125.
- Some rules (particularly #2 and #6) reflect historical limitations and may evolve as mempool policy improves.

---

## History

*Pending*
