# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/lesson_11_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/lesson_11_autogen.dir/ParseCache.txt"
  "lesson_11_autogen"
  )
endif()
