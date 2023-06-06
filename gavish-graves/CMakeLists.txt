cmake_minimum_required(VERSION 3.10)

add_executable(gavish-graves
        main.cpp
        GavishGraves.h
        GavishGraves.cpp)

target_link_libraries(gavish-graves
        coordinate
        exceptions
        path
        tsp-file
        tsp-readers
        tsp-solvers
        utils)
target_link_libraries(gavish-graves ${cplex_libraries})