cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 99)

project(
  RouteFinder
  DESCRIPTION "Finds the shortest route between two given nodes given a set of nodes and edges"
  LANGUAGES C
)

include(CTest)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(extern/Unity)
add_subdirectory(extern/gnuplot_i)
