cmake_minimum_required(VERSION 3.10)

add_executable(nearest-neighbour
        main.cpp
        NearestNeighbour.h
        NearestNeighbour.cpp)

target_link_libraries(nearest-neighbour
        coordinate
        exceptions
        path
        tsp-file
        tsp-readers
        tsp-solvers
        utils)