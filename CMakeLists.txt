cmake_minimum_required (VERSION 2.6)
project (TapTempo)

set (TAPTEMPO_VERSION_MAJOR 0)
set (TAPTEMPO_VERSION_MINOR 1)
set (TAPTEMPO_VERSION_REVISION 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/taptempo_config.h.in"
  "${PROJECT_BINARY_DIR}/taptempo_config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

  
add_executable(TapTempo main.cpp taptempo.cpp)

