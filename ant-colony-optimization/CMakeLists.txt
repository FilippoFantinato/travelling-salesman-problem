cmake_minimum_required(VERSION 3.10)

add_library(ant-colony-optimization
        ACO.h
        ACO.cpp)

add_executable(ant-colony-optimization-bin main.cpp)
target_link_libraries(ant-colony-optimization-bin
        ant-colony-optimization
        nearest-neighbour
        libraries)
set_target_properties(ant-colony-optimization-bin
        PROPERTIES OUTPUT_NAME ant-colony-optimization)
