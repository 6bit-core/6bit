# 1. Multisig Tutorial

Currently, it is possible to create a multisig wallet using Sixbit Core only.

This tutorial uses [jq](https://github.com/stedolan/jq) JSON processor to process the results from RPC and stores the relevant values in bash variables. This makes the tutorial reproducible and easier to follow step by step.

Before starting this tutorial, start the sixbit node on the signet network.

```bash
./build/bin/sixbitd -signet -daemon
```

This tutorial also uses the default WPKH derivation path to get the xpubs and does not conform to BIP 45 or BIP 87.

At the time of writing, there is no way to extract a specific path from wallets in Sixbit Core. For this, an external signer/xpub can be used.

## 1.1 Basic Multisig Workflow

### 1.1 Create the Descriptor Wallets

For a 2-of-3 multisig, create 3 descriptor wallets. These wallets contain HD seed and private keys, used to sign PSBTs and derive xpubs.

```bash
for ((n=1;n<=3;n++))
do
 ./build/bin/sixbit-cli -signet createwallet "participant_${n}"
done
```

### 1.2 Define the Multisig Descriptors

Define descriptors:

```bash
external_desc="wsh(sortedmulti(2,...))"
internal_desc="wsh(sortedmulti(2,...))"
```

Then compute checksum using:

```bash
./build/bin/sixbit-cli -signet getdescriptorinfo $external_desc
```

### 1.3 Create the Multisig Wallet

```bash
./build/bin/sixbit-cli -signet -named createwallet wallet_name="multisig_wallet_01" disable_private_keys=true blank=true
```

### 1.4 Fund the Wallet

```bash
receiving_address=$(./build/bin/sixbit-cli -signet -rpcwallet="multisig_wallet_01" getnewaddress)
```

### 1.5 Create a PSBT

```bash
funded_psbt=$(./build/bin/sixbit-cli -signet walletcreatefundedpsbt ...)
```

### 1.6 Analyze the PSBT

```bash
./build/bin/sixbit-cli -signet analyzepsbt $funded_psbt
```

### 1.7 Sign the PSBT

```bash
walletprocesspsbt
```

### 1.8 Combine

```bash
combinepsbt
```

### 1.9 Finalize and Broadcast

```bash
finalizepsbt
sendrawtransaction
```

### 1.10 Sequential Signing Alternative

Sequential signing is also supported.
