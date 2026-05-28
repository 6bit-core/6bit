# Unauthenticated REST Interface (Sixbit Core)

The REST API can be enabled with the `-rest` option.

## Ports

The interface runs on the same port as JSON-RPC:

- Mainnet: 16665  
- Testnet: 26665  
- Testnet4: 26665  
- Signet: 56665
- Regtest: 46665  

---

## Consistency Guarantees

Same guarantees as the JSON-RPC interface apply.

---

## Limitations

High numbers of simultaneous HTTP connections may exhaust file descriptors and crash the node.

Recommendations:
- Increase system file descriptor limits
- Avoid excessive concurrent REST requests

---

## Supported API

### Transactions
`GET /rest/tx/<TX-HASH>.<bin|hex|json>`

- Returns transaction data
- Default: mempool only
- Requires `txindex=1` for confirmed transactions

---

### Blocks
- `/rest/block/<BLOCK-HASH>.<bin|hex|json>`
- `/rest/block/notxdetails/<BLOCK-HASH>.<bin|hex|json>`

Returns full block data.

---

### Block Headers
`GET /rest/headers/<BLOCK-HASH>.<bin|hex|json>?count=<COUNT>`

Returns multiple headers forward from a block.

---

### Blockfilters
- `/rest/blockfilter/<FILTERTYPE>/<BLOCK-HASH>`
- `/rest/blockfilterheaders/<FILTERTYPE>/<BLOCK-HASH>`

---

### Blockhash by Height
`GET /rest/blockhashbyheight/<HEIGHT>.<bin|hex|json>`

---

### UTXO Queries
- `/rest/getutxos/...`
- `/rest/getutxos/checkmempool/...`

Allows querying UTXO set.

---

### Chain Info
`GET /rest/chaininfo.json`

---

### Deployment Info
`GET /rest/deploymentinfo.json`

---

### Mempool
- `/rest/mempool/info.json`
- `/rest/mempool/contents.json`

---

## Risks

Running a browser on the same machine may expose node data via XSS attacks.

Example:
<script src="http://1.0.0.1:16665/rest/tx/..."></script>

Mitigation:
- Avoid untrusted websites
- Use firewall rules if needed
