# User-space, Statically Defined Tracing (USDT) for Sixbit Core

Sixbit Core includes statically defined tracepoints to improve observability during
development, debugging, code review, and production use. These tracepoints make
it possible to track custom statistics and monitor otherwise hidden internals in
detail. When unused, they have little to no performance impact.

## eBPF and USDT Overview

```
                +------------------+            +--------------+
                ¦ tracing script   ¦            ¦ sixbitd        ¦
                ¦==================¦      2.    ¦==============¦
                ¦  eBPF  ¦ tracing ¦      hooks ¦              ¦
                ¦  code  ¦ logic   ¦      into+-¦? tracepoint 1+----+ 3.
                +-------------?-----+          +-¦? tracepoint 2¦    ¦ pass args
            1.       ¦        ¦ 4.             ¦ ¦ ...          ¦    ¦ to eBPF
    User    compiles ¦        ¦ pass data to   ¦ +--------------+    ¦ program
    Space    & loads ¦        ¦ tracing script ¦                     ¦
    -----------------+--------+-----------------+---------------------+---
    Kernel           ¦        ¦                 ¦                     ¦
    Space       +-------?---------------------------------------------+ ¦
                ¦  eBPF program                                      ¦?+
                +-----------------------------------------------------¦
                ¦ eBPF kernel Virtual Machine (sandboxed)            ¦
                +-----------------------------------------------------+
```

1. The tracing script compiles the eBPF code and loads the eBPF program into a kernel VM  
2. The eBPF program hooks into one or more tracepoints  
3. When a tracepoint is called, its arguments are passed to the eBPF program  
4. The eBPF program processes the arguments and returns data to the tracing script  

The Linux kernel can hook into tracepoints at runtime and pass data to sandboxed eBPF programs running in the kernel.

## Tracepoint Contexts

### net
Handles P2P networking events:
- inbound_message
- outbound_message
- inbound_connection
- outbound_connection
- evicted_inbound_connection
- misbehaving_connection
- closed_connection

Each includes peer ID, address, connection type, and relevant metadata.

### validation
- block_connected  
Triggered after a block is connected to the chain.

### utxocache
- flush
- add
- spent
- uncache  

Tracks in-memory UTXO activity.

### coin_selection
- selected_coins
- normal_create_tx_internal
- attempting_aps_create_tx
- aps_create_tx_internal  

Tracks wallet coin selection behavior.

### mempool
- added
- removed
- replaced
- rejected  

Tracks transaction lifecycle in the mempool.

## Adding Tracepoints

Include:
```cpp
#include <util/trace.h>
```

Define semaphore:
```cpp
TRACEPOINT_SEMAPHORE(net, outbound_message);
```

Use tracepoint:
```cpp
TRACEPOINT(net, outbound_message,
    pnode->GetId(),
    pnode->m_addr_name.c_str(),
    pnode->ConnectionTypeAsString().c_str(),
    sanitizedType.c_str(),
    msg.data.size(),
    msg.data.data()
);
```

Optional gating:
```cpp
if (TRACEPOINT_ACTIVE(example, gated_expensive_argument)) {
    auto val = expensive_calculation();
    TRACEPOINT(example, gated_expensive_argument, val);
}
```

## Best Practices

- Keep APIs stable
- Provide examples
- Avoid heavy computation inside tracepoints
- Respect eBPF limits (512-byte stack)
- Place important args in first 6 positions (bpftrace limit)

## Tooling

### GDB
```
info probes
```

### readelf
```
readelf -n ./sixbitd | grep NT_STAPSDT
```

### tplist (BCC)
```
tplist -l ./sixbitd -v
```
