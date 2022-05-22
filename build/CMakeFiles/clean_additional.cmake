# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\npc-generator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\npc-generator_autogen.dir\\ParseCache.txt"
  "npc-generator_autogen"
  )
endif()
