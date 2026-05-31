# CMake generated Testfile for 
# Source directory: /home/ubuntu/6bit/src/secp256k1/src
# Build directory: /home/ubuntu/6bit/build-win64/src/secp256k1/src
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[secp256k1_noverify_tests]=] "/home/ubuntu/6bit/build-win64/src/secp256k1/bin/noverify_tests.exe")
set_tests_properties([=[secp256k1_noverify_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/ubuntu/6bit/src/secp256k1/src/CMakeLists.txt;139;add_test;/home/ubuntu/6bit/src/secp256k1/src/CMakeLists.txt;0;")
add_test([=[secp256k1_tests]=] "/home/ubuntu/6bit/build-win64/src/secp256k1/bin/tests.exe")
set_tests_properties([=[secp256k1_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/ubuntu/6bit/src/secp256k1/src/CMakeLists.txt;144;add_test;/home/ubuntu/6bit/src/secp256k1/src/CMakeLists.txt;0;")
add_test([=[secp256k1_exhaustive_tests]=] "/home/ubuntu/6bit/build-win64/src/secp256k1/bin/exhaustive_tests.exe")
set_tests_properties([=[secp256k1_exhaustive_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/ubuntu/6bit/src/secp256k1/src/CMakeLists.txt;153;add_test;/home/ubuntu/6bit/src/secp256k1/src/CMakeLists.txt;0;")
