# Assumeutxo Usage

Assumeutxo is a feature that allows fast bootstrapping of a validating sixbitd instance.

For notes on the design of Assumeutxo, please refer to:
doc/design/assumeutxo.md

## Loading a snapshot

There is currently no canonical source for snapshots, but any downloaded snapshot
will be checked against a hash hardcoded in source code.

Load snapshot:

```
sixbit-cli -rpcclienttimeout=0 loadtxoutset /path/to/input
```

Monitor sync:

```
getchainstates
```

### Pruning

- Minimum prune: 550 MiB
- Assumeutxo uses ~1100 MiB minimum
- Two chainstates temporarily exist

### Indexes

- Indexes do NOT benefit from Assumeutxo
- Always build from genesis
- Cannot prune unindexed blocks

## Generating a snapshot

```
sixbit-cli -rpcclienttimeout=0 dumptxoutset /path/to/output rollback
```

Notes:
- Node enters temporary inconsistent state
- Network activity disabled during process
- Increase RPC timeout: `-rpcclienttimeout=0`
