cmake_minimum_required(VERSION 3.22)

project(sixbit-tidy
    VERSION 1.0.0
    DESCRIPTION "clang-tidy checks for Sixbit Core"
    LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(CMAKE_DISABLE_FIND_PACKAGE_CURL ON)
set(CMAKE_DISABLE_FIND_PACKAGE_FFI ON)
set(CMAKE_DISABLE_FIND_PACKAGE_LibEdit ON)
set(CMAKE_DISABLE_FIND_PACKAGE_LibXml2 ON)
set(CMAKE_DISABLE_FIND_PACKAGE_Terminfo ON)
set(CMAKE_DISABLE_FIND_PACKAGE_ZLIB ON)
set(CMAKE_DISABLE_FIND_PACKAGE_zstd ON)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

find_program(CLANG_TIDY_EXE
    NAMES "clang-tidy-${LLVM_VERSION_MAJOR}" "clang-tidy"
    HINTS ${LLVM_TOOLS_BINARY_DIR})

if(NOT CLANG_TIDY_EXE)
    message(FATAL_ERROR "clang-tidy executable not found")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")

add_library(sixbit-tidy MODULE sixbit-tidy.cpp nontrivial-threadlocal.cpp)
target_include_directories(sixbit-tidy SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
target_compile_definitions(sixbit-tidy PRIVATE ${LLVM_DEFINITIONS})

# Disable RTTI and exceptions as necessary
if (MSVC)
    target_compile_options(sixbit-tidy PRIVATE /GR-)
else()
    target_compile_options(sixbit-tidy PRIVATE -fno-rtti -fno-exceptions)
endif()

if(CMAKE_HOST_APPLE)
    # ld64 expects no undefined symbols by default
    target_link_options(sixbit-tidy PRIVATE -Wl,-flat_namespace)
    target_link_options(sixbit-tidy PRIVATE -Wl,-undefined -Wl,suppress)
endif()

# Add warnings
if (MSVC)
    target_compile_options(sixbit-tidy PRIVATE /W4)
else()
    target_compile_options(sixbit-tidy PRIVATE -Wall -Wextra)
endif()

if(CMAKE_VERSION VERSION_LESS 3.27)
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "--load=${CMAKE_BINARY_DIR}/${CMAKE_SHARED_MODULE_PREFIX}sixbit-tidy${CMAKE_SHARED_MODULE_SUFFIX}" "-checks=-*,sixbit-*")
else()
    # CLANG_TIDY_COMMAND supports generator expressions as of 3.27
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "--load=$<TARGET_FILE:sixbit-tidy>" "-checks=-*,sixbit-*")
endif()

# Create a dummy library that runs clang-tidy tests as a side-effect of building
add_library(sixbit-tidy-tests OBJECT EXCLUDE_FROM_ALL example_nontrivial-threadlocal.cpp)
add_dependencies(sixbit-tidy-tests sixbit-tidy)

set_target_properties(sixbit-tidy-tests PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")


install(TARGETS sixbit-tidy LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
