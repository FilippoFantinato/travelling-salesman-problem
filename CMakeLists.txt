cmake_minimum_required(VERSION 3.10)

project(TSP)
set(CMAKE_CXX_FLAGS "-g -Wall -O2")
set(CMAKE_MODULE_LINKER_FLAGS "-lcplex -lm -pthread -ldl")

set(CPLEX_INC_DIR "/opt/ibm/ILOG/CPLEX_Studio128/cplex/include")
set(CPLEX_STATIC "/opt/ibm/ILOG/CPLEX_Studio128/cplex/lib/x86-64_linux/static_pic")

find_package(Threads)

# =====================================================================================
file(GLOB cplex_libraries ${CPLEX_STATIC}/*.a)
include_directories(${CPLEX_INC_DIR})

add_subdirectory(libraries)
add_subdirectory(nearest-neighbour)
add_subdirectory(ant-system)
add_subdirectory(ant-colony-system)
add_subdirectory(gavish-graves)

# =====================================================================================
add_executable(tsp
        main.cpp
        CLI/CLI.h
        CLI/CLI.cpp
        CLI/initializers.h
        CLI/initializers.cpp)

target_link_libraries(tsp
        ant-system
        ant-colony-system
        gavish-graves
        nearest-neighbour
        libraries)
target_link_libraries(tsp
        ${cplex_libraries}
        ${CMAKE_THREAD_LIBS_INIT}
        ${CMAKE_DL_LIBS})
