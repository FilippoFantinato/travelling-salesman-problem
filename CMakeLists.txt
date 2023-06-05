cmake_minimum_required(VERSION 3.24)

project(lin-kernighan)
set(CMAKE_CXX_FLAGS "-g -Wall -O2")
set(CMAKE_MODULE_LINKER_FLAGS "-lcplex -lm -pthread -ldl")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

set(CPLEX_INC_DIR "/opt/ibm/ILOG/CPLEX_Studio2211/cplex/include")
set(CPLEX_STATIC "/opt/ibm/ILOG/CPLEX_Studio2211/cplex/lib/x86-64_linux/static_pic")

file(GLOB cplex_libraries ${CPLEX_STATIC}/*.a)
add_subdirectory(libraries)

# =====================================================================================
add_executable(ant-colony-optimization
        ant-colony-optimization/main.cpp
        ant-colony-optimization/ACO.h
        ant-colony-optimization/ACO.cpp)

target_link_libraries(ant-colony-optimization
        coordinate
        exceptions
        path
        tsp-file
        tsp-readers
        tsp-solvers
        utils)

# =====================================================================================
include_directories(${CPLEX_INC_DIR})
add_executable(gavish-graves
        gavish-graves/main.cpp
        gavish-graves/GavishGraves.h
        gavish-graves/GavishGraves.cpp)

target_link_libraries(gavish-graves
        coordinate
        exceptions
        path
        tsp-file
        tsp-readers
        tsp-solvers
        utils)
target_link_libraries(gavish-graves ${cplex_libraries})
