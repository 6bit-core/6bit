# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "src/qt/CMakeFiles/sixbit-qt_autogen.dir/AutogenUsed.txt"
  "src/qt/CMakeFiles/sixbit-qt_autogen.dir/ParseCache.txt"
  "src/qt/CMakeFiles/sixbitqt_autogen.dir/AutogenUsed.txt"
  "src/qt/CMakeFiles/sixbitqt_autogen.dir/ParseCache.txt"
  "src/qt/sixbit-qt_autogen"
  "src/qt/sixbitqt_autogen"
  "src/qt/test/CMakeFiles/test_sixbit-qt_autogen.dir/AutogenUsed.txt"
  "src/qt/test/CMakeFiles/test_sixbit-qt_autogen.dir/ParseCache.txt"
  "src/qt/test/test_sixbit-qt_autogen"
  )
endif()
