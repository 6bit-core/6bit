# Copyright (c) 2026-present The Sixbit Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

function(add_libmultiprocess subdir)
  set(BUILD_TESTING "${BUILD_TESTS}")
  add_subdirectory(${subdir} EXCLUDE_FROM_ALL)

  foreach(t multiprocess mputil mpgen)
    if(TARGET ${t})
      target_link_libraries(${t} PRIVATE $<BUILD_INTERFACE:core_interface>)
    endif()
  endforeach()

  mark_as_advanced(CapnProto_DIR)
  mark_as_advanced(CapnProto_capnpc_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_capnp_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_capnp-json_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_capnp-rpc_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_capnp-websocket_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_kj-async_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_kj-gzip_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_kj-http_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_kj_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_kj-test_IMPORTED_LOCATION)
  mark_as_advanced(CapnProto_kj-tls_IMPORTED_LOCATION)

  if(BUILD_TESTS AND TARGET mptests)
    set_target_properties(mptests PROPERTIES EXCLUDE_FROM_ALL OFF)
  endif()

  foreach(t mpcalculator mpprinter mpexample)
    if(TARGET ${t})
      set_target_properties(${t} PROPERTIES EXPORT_COMPILE_COMMANDS OFF)
    endif()
  endforeach()
endfunction()