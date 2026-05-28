# Copyright (c) 2019-present The Bitcoin Core developers
# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

add_library(sixbit_zmq STATIC EXCLUDE_FROM_ALL
  zmqabstractnotifier.cpp
  zmqnotificationinterface.cpp
  zmqpublishnotifier.cpp
  zmqrpc.cpp
  zmqutil.cpp
)
target_compile_definitions(sixbit_zmq
  INTERFACE
    ENABLE_ZMQ=1
)
target_link_libraries(sixbit_zmq
  PRIVATE
    core_interface
    univalue
    zeromq
)
