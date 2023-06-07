cmake_minimum_required(VERSION 3.10)

add_library(nearest-neighbour
        NearestNeighbour.h
        NearestNeighbour.cpp)

add_executable(nearest-neighbour-bin main.cpp)
target_link_libraries(nearest-neighbour-bin
        nearest-neighbour
        libraries)
set_target_properties(nearest-neighbour-bin
        PROPERTIES OUTPUT_NAME nearest-neighbour)
