# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\work5_qq_cmake_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\work5_qq_cmake_autogen.dir\\ParseCache.txt"
  "work5_qq_cmake_autogen"
  )
endif()
