# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

function(generate_setup_nsi)
  set(abs_top_srcdir ${PROJECT_SOURCE_DIR})
  set(abs_top_builddir ${PROJECT_BINARY_DIR})
  set(CLIENT_URL ${PROJECT_HOMEPAGE_URL})
  set(CLIENT_TARNAME "sixbit")
  set(SIXBIT_WRAPPER_NAME "sixbit")
  set(SIXBIT_GUI_NAME "sixbit-qt")
  set(SIXBIT_DAEMON_NAME "sixbitd")
  set(SIXBIT_CLI_NAME "sixbit-cli")
  set(SIXBIT_TX_NAME "sixbit-tx")
  set(SIXBIT_WALLET_TOOL_NAME "sixbit-wallet")
  set(SIXBIT_TEST_NAME "test_sixbit")
  set(EXEEXT ${CMAKE_EXECUTABLE_SUFFIX})
  configure_file(${PROJECT_SOURCE_DIR}/share/setup.nsi.in ${PROJECT_BINARY_DIR}/sixbit-win64-setup.nsi USE_SOURCE_PERMISSIONS @ONLY)
endfunction()