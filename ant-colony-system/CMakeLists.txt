cmake_minimum_required(VERSION 3.24)

add_executable(ant-colony-system
        main.cpp
        ACS.h
        ACS.cpp
        ../nearest-neighbour/NearestNeighbour.h
        ../nearest-neighbour/NearestNeighbour.cpp)

target_link_libraries(ant-colony-system
        coordinate
        exceptions
        path
        tsp-file
        tsp-readers
        tsp-solvers
        utils)
