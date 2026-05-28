# Support for signing transactions outside of Sixbit Core

Sixbit Core can be launched with `-signer=<cmd>`, where `<cmd>` is an external program that can sign transactions and perform other functions. For example, it can be used to communicate with a hardware wallet.

## Example usage

The following example is based on the HWI tool. Version 2.0 or later is required. Although this tool is hosted under the Sixbit Core GitHub organization and maintained by Sixbit Core developers, it should be used with caution. It is considered experimental and has received far less review than Sixbit Core itself. Be especially careful when running tools like these on a computer that holds private keys.

Start Sixbit Core:

    $ sixbitd -signer=../HWI/hwi.py

### Device setup

Follow the hardware manufacturer’s instructions for setup and backup.

### Create wallet and import keys

    $ sixbit-cli enumeratesigners

Create wallet:

    $ sixbit-cli createwallet "hww" true true "" true true true

### Verify an address

    $ sixbit-cli -rpcwallet=<wallet> getnewaddress
    $ sixbit-cli -rpcwallet=<wallet> walletdisplayaddress <address>

### Spending

    $ sixbit-cli -rpcwallet=<wallet> sendtoaddress <address> <amount>

Returns:

    {"complete": true, "txid": "<txid>"}

## Signer API

### enumerate (required)

    $ <cmd> enumerate
    [
      {"fingerprint": "00000000"}
    ]

### signtransaction (required)

    $ <cmd> --fingerprint=<fingerprint> signtransaction <psbt>

Returns a signed PSBT.

### getdescriptors (optional)

    $ <cmd> --fingerprint=<fingerprint> getdescriptors 0

### displayaddress (optional)

    $ <cmd> --fingerprint=<fingerprint> displayaddress --desc <descriptor>

Returns:

    {"address": "[the address]"}

## How Sixbit Core uses the Signer API

- enumeratesigners ? `<cmd> enumerate`
- createwallet ? `<cmd> getdescriptors`
- walletdisplayaddress ? `<cmd> displayaddress`
- sendtoaddress ? `<cmd> signtransaction`
