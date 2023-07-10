cmake_minimum_required(VERSION 3.10)

add_library(ant-colony-system
        AntColonySystem.h
        AntColonySystem.cpp)

add_executable(ant-colony-system-bin main.cpp)
target_link_libraries(ant-colony-system-bin
        ant-colony-system
        nearest-neighbour
        libraries)
set_target_properties(ant-colony-system-bin
        PROPERTIES OUTPUT_NAME ant-colony-system)
