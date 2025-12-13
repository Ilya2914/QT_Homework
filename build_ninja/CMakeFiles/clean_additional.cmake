# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles/keyboard_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/keyboard_autogen.dir/ParseCache.txt"
  "keyboard_autogen"
  )
endif()
