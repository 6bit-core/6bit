# Block and Transaction Broadcasting with ZeroMQ

[ZeroMQ](https://zeromq.org/) is a lightweight wrapper around TCP
connections, inter-process communication, and shared-memory,
providing various message-oriented semantics such as publish/subscribe,
request/reply, and push/pull.

The Sixbit Core daemon can be configured to act as a trusted "border
router", implementing the sixbit wire protocol and relay, making
consensus decisions, maintaining the local blockchain database,
broadcasting locally generated transactions into the network, and
providing a queryable RPC interface to interact on a polled basis for
requesting blockchain related data. However, there exists only a
limited service to notify external software of events like the arrival
of new blocks or transactions.

The ZeroMQ facility implements a notification interface through a set
of specific notifiers. Currently there are notifiers that publish
blocks and transactions. This read-only facility requires only the
connection of a corresponding ZeroMQ subscriber port in receiving
software; it is not authenticated nor is there any two-way protocol
involvement. Therefore, subscribers should validate the received data
since it may be out of date, incomplete or even invalid.

ZeroMQ sockets are self-connecting and self-healing; that is,
connections made between two endpoints will be automatically restored
after an outage, and either end may be freely started or stopped in
any order.

Because ZeroMQ is message oriented, subscribers receive transactions
and blocks all-at-once and do not need to implement any sort of
buffering or reassembly.

## Prerequisites

The ZeroMQ feature in Sixbit Core requires the ZeroMQ API >= 1.0.0
[libzmq](https://github.com/zeromq/libzmq/releases).

## Enabling

To enable, use:

    cmake -B build -DWITH_ZMQ=ON

## Usage

    -zmqpubhashtx=address
    -zmqpubhashblock=address
    -zmqpubrawblock=address
    -zmqpubrawtx=address
    -zmqpubsequence=address

## Message format

| topic     | body                                                 | sequence |
|-----------|------------------------------------------------------|----------|
| rawtx     | serialized transaction                               | uint32   |
| hashtx    | reversed tx hash                                     | uint32   |
| rawblock  | serialized block                                     | uint32   |
| hashblock | reversed block hash                                  | uint32   |

## Notes

- Hashes are reversed byte order
- Messages may be duplicated (mempool + block inclusion)
- Sequence numbers help detect lost messages
