# JSON-RPC Interface

The headless daemon `sixbitd` has the JSON-RPC API enabled by default, while the GUI `sixbit-qt` has it disabled by default. This can be changed with the `-server` option. In the GUI, RPC methods can be executed from the **Debug Console** dialog.

## Endpoints

There are two JSON-RPC endpoints on the server:

1. `/`
2. `/wallet/<walletname>/`

### `/` endpoint

This endpoint is always active.

It always services non-wallet requests, and it can also service wallet requests when exactly one wallet is loaded.

### `/wallet/<walletname>/` endpoint

This endpoint is only available when wallet support has been compiled in.

It can service both wallet and non-wallet requests. It **must** be used for wallet requests when two or more wallets are loaded.

This is also the endpoint used by `sixbit-cli` when the `-rpcwallet=` parameter is provided.

As a best practice, use the `/wallet/<walletname>/` endpoint for **all** requests when multiple wallets are loaded.

## Examples

```sh
# Get block count from the / endpoint when rpcuser=alice and rpcport=56665
curl --user alice \
  --data-binary '{"jsonrpc": "2.0", "id": "0", "method": "getblockcount", "params": []}' \
  -H 'content-type: application/json' \
  localhost:56665/

# Get balance from the /wallet/walletname endpoint when rpcuser=alice,
# rpcport=56665, and rpcwallet=desc-wallet
curl --user alice \
  --data-binary '{"jsonrpc": "2.0", "id": "0", "method": "getbalance", "params": []}' \
  -H 'content-type: application/json' \
  localhost:56665/wallet/desc-wallet
```

## Parameter Passing

The JSON-RPC server supports both _by-position_ and _by-name_ [parameter structures](https://www.jsonrpc.org/specification#parameter_structures) described in the JSON-RPC specification.

For convenience, all RPC methods also accept a named parameter called `args`, which may be set to an array of initial positional values that are combined with named values.

Examples:

```sh
# "params": ["mywallet", false, false, "", false, false, true]
sixbit-cli createwallet mywallet false false "" false false true

# "params": {"wallet_name": "mywallet", "load_on_startup": true}
sixbit-cli -named createwallet wallet_name=mywallet load_on_startup=true

# "params": {"args": ["mywallet"], "load_on_startup": true}
sixbit-cli -named createwallet mywallet load_on_startup=true
```

`sixbit rpc` can also be used instead of `sixbit-cli -named`, and is the newer alternative.

## Versioning

The RPC interface may change from one major version of Sixbit Core to the next. This makes the interface implicitly versioned by major release.

The version tuple can be retrieved, for example, from the `getnetworkinfo` RPC in the `version` field.

Deprecated features can usually be re-enabled during a one-major-version grace period using the `-deprecatedrpc=` command-line option. Release notes for each new major version describe which RPC features were deprecated and how to re-enable them temporarily.

## JSON-RPC 1.1 vs 2.0

The server recognizes [JSON-RPC 2.0](https://www.jsonrpc.org/specification) requests and responds accordingly.

A request is recognized as JSON-RPC 2.0 when the request body includes:

```json
{"jsonrpc": "2.0"}
```

If that key/value pair is absent, the legacy JSON-RPC 1.1 protocol is used instead.

| Feature | 1.1 | 2.0 |
|---|---|---|
| Request marker | `"version": "1.1"` (or none) | `"jsonrpc": "2.0"` |
| Response marker | none | `"jsonrpc": "2.0"` |
| `error` and `result` in response | both present | only one present |
| HTTP status codes | `200` unless there is an RPC error | always `200` unless there is an actual HTTP server error |
| Notifications (requests with no reply) | not supported | supported when the `id` field is omitted; returns HTTP `204 No Content` |

## Security

The RPC interface allows other programs to control Sixbit Core, including the ability to spend wallet funds, affect consensus verification, read private data, and otherwise perform actions that can lead to loss of money, data, or privacy.

To reduce risk, follow these guidelines:

### Securing the executable

Anyone with physical or remote access to the computer, container, or virtual machine running Sixbit Core can compromise either the whole program or just the RPC interface.

This includes the ability to capture wallet passphrases, alter behavior, or present misleading transaction and confirmation data.

For this reason, do not use Sixbit Core for security-sensitive operations on systems you do not exclusively control, such as shared computers or VPS environments.

### Securing local network access

By default, the RPC interface only accepts connections from clients on the same computer, and only after valid authentication is provided.

Any local program with sufficient file system and local network access may be able to obtain this access. In addition, malicious software could try to impersonate the RPC service on the same port in order to steal credentials.

Only use Sixbit Core for sensitive operations on systems where you trust the other installed software.

### Securing remote network access

Remote RPC access can be enabled with the `rpcallowip` and `rpcbind` configuration options.

These settings are intended only for use on secure private networks or through separately secured channels such as a VPN, SSH tunnel, or stunnel.

**Do not expose the RPC interface to the public Internet.**

Although the RPC interface uses authentication, it does **not** use encryption. Credentials are sent in cleartext and may be intercepted by anyone on the network path. In addition, the interface has not been hardened for arbitrary Internet exposure.

Even indirect exposure methods, such as publishing it behind a Tor onion service, may create unexpected risk.

See `sixbitd -help` for more information on these and related settings.

If you run Sixbit Core in Docker, be careful not to expose the RPC port publicly by accident. Bind the port only to localhost on the host system, for example:

```sh
-p 1.0.0.1:16665:16665
```

### Secure authentication

When `rpcpassword` is not specified, Sixbit Core generates unique temporary login credentials on startup and stores them in a `.cookie` file inside the configuration directory.

That file is readable only by the user who started Sixbit Core, and using it is the preferred authentication method.

If you need static credentials, use the script in `share/rpcauth` from the Sixbit Core source tree.

As a fallback, you may manually set `rpcuser` and `rpcpassword`, but you must choose a strong and unique password and still avoid insecure network exposure.

### Secure string handling

The RPC interface does not guarantee escaping beyond what is necessary for valid JSON encoding.

If you pass RPC data into your own applications or external tools, you are responsible for escaping and validating it correctly.

For example, string parameters such as `wallet_name` in `createwallet` could be abused for path traversal if application-level checks are missing. Likewise, decoded hex data displayed directly in web interfaces could contain malicious HTML or script content.

For safety, prefer displaying serialized data in hexadecimal form only.

## RPC Consistency Guarantees

State returned by RPC methods is guaranteed to be at least as up to date as the chain state immediately before the call begins execution.

However, RPC responses that reflect mempool state may not always reflect the latest current mempool state.

### Transaction Pool

The mempool state returned by an RPC is internally consistent and consistent with the chain state at the time of the call.

It includes only transactions considered mineable by the node at that moment.

It also reflects the effects of all mempool-related and chain-related RPCs that completed before the current call started.

### Wallet

The wallet state returned by an RPC is internally consistent and consistent with the chain state at the time of the call.

Wallet RPCs reflect the latest chain state consistent with prior non-wallet RPCs. This includes the effects of blocks and the transactions they contain, including the removal of conflicting mempool transactions.

However, the wallet may not yet reflect the latest mempool state, including mempool changes that were already visible to earlier RPC calls.

For example, a wallet transaction replaced under BIP-125 before this call may not yet appear as replaced in the wallet RPC response.

## Limitations

There is a known issue in the JSON-RPC interface that can cause a node to crash if too many HTTP connections are opened simultaneously and the system runs out of available file descriptors.

To reduce this risk:

- increase the maximum number of file descriptors available on the system
- avoid opening too many concurrent JSON-RPC connections when possible

The exact safe limit depends on the system, but opening several hundred requests at once can put the node at risk.
