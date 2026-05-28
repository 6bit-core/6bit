# Copyright (c) 2019-present The Bitcoin Core developers
# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

set(CMAKE_AUTOMOC_MOC_OPTIONS "-p${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(test_sixbit-qt
  apptests.cpp
  optiontests.cpp
  rpcnestedtests.cpp
  test_main.cpp
  uritests.cpp
  util.cpp
  ../../init/sixbit-qt.cpp
)

target_link_libraries(test_sixbit-qt
  core_interface
  sixbitqt
  test_util
  sixbit_node
  Boost::headers
  Qt6::Test
  Qt6::Core
  Qt6::Widgets
)

import_plugins(test_sixbit-qt)

if(ENABLE_WALLET)
  target_sources(test_sixbit-qt
    PRIVATE
      addressbooktests.cpp
      wallettests.cpp
      ../../wallet/test/wallet_test_fixture.cpp
  )
endif()

add_test(NAME test_sixbit-qt
  COMMAND test_sixbit-qt
)

if(WIN32 AND VCPKG_TARGET_TRIPLET)
  # On Windows, vcpkg configures Qt with `-opengl dynamic`, which makes
  # the "minimal" platform plugin unusable due to internal Qt bugs.
  set_tests_properties(test_sixbit-qt PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=windows"
  )
endif()

install_binary_component(test_sixbit-qt INTERNAL)
