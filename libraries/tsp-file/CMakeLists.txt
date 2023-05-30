cmake_minimum_required(VERSION 3.24)

include_directories(exceptions ../exceptions)

add_library(tsp-file
        tsp-file.h
        tsp-file.cpp
        TSPInformation.h
        TSPInformation.cpp
        TSPSection.h
        TSPSection.cpp
        types.h)

target_link_libraries(tsp-file exceptions)
