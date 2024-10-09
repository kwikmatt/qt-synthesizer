# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Practicing_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Practicing_autogen.dir\\ParseCache.txt"
  "Practicing_autogen"
  )
endif()
