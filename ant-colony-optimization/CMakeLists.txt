cmake_minimum_required(VERSION 3.24)

add_executable(ant-colony-optimization
        main.cpp
        ACO.h
        ACO.cpp
        ../nearest-neighbour/NearestNeighbour.h
        ../nearest-neighbour/NearestNeighbour.cpp)

target_link_libraries(ant-colony-optimization
        coordinate
        exceptions
        path
        tsp-file
        tsp-readers
        tsp-solvers
        utils)