cmake_minimum_required(VERSION 3.10)

project(lin-kernighan)
set(CMAKE_CXX_FLAGS "-g -Wall -O2")
set(CMAKE_MODULE_LINKER_FLAGS "-lcplex -lm -pthread -ldl")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set(CPLEX_INC_DIR "/opt/ibm/ILOG/CPLEX_Studio2211/cplex/include")
set(CPLEX_STATIC "/opt/ibm/ILOG/CPLEX_Studio2211/cplex/lib/x86-64_linux/static_pic")

file(GLOB cplex_libraries ${CPLEX_STATIC}/*.a)
include_directories(${CPLEX_INC_DIR})
add_subdirectory(libraries)

# =====================================================================================
add_subdirectory(nearest-neighbour)

# =====================================================================================
add_subdirectory(ant-colony-optimization)

# =====================================================================================
add_subdirectory(ant-colony-system)

# =====================================================================================
add_subdirectory(gavish-graves)
