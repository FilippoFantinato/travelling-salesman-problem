cmake_minimum_required(VERSION 3.10)


include_directories(${CPLEX_INC_DIR})
file(GLOB_RECURSE libraries_sources "*.cpp" "*.h")
add_library(libraries ${libraries_sources})
