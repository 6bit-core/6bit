# Copyright (c) 2019-present The Bitcoin Core developers
# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

include(ts_files.cmake)

if(Qt6_VERSION VERSION_GREATER_EQUAL 6.7)
  qt6_add_lrelease(TS_FILES ${ts_files} LRELEASE_TARGET sixbitqt_lrelease OPTIONS -silent)
else()
  qt6_add_lrelease(sixbitqt TS_FILES ${ts_files} OPTIONS -silent)
endif()

add_dependencies(sixbitqt sixbitqt_lrelease)
