cmake_minimum_required(VERSION 3.24)

include_directories(coordinate ../coordinate)
include_directories(utils ../utils)
include_directories(tsp_file ../tsp-file)

add_library(tsp-readers
        att.h
        att.cpp
        euc2d.h
        euc2d.cpp
        full_matrix.h
        full_matrix.cpp
        geo.h
        geo.cpp
        upper_row.h
        upper_row.cpp
)

target_link_libraries(tsp-readers coordinate utils tsp-file)
