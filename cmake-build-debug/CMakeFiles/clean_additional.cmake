# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CG_autogen"
  "CMakeFiles/CG_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CG_autogen.dir/ParseCache.txt"
  )
endif()
