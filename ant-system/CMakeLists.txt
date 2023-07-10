cmake_minimum_required(VERSION 3.10)

add_library(ant-system
        AntSystem.h
        AntSystem.cpp)

add_executable(ant-system-bin main.cpp)
target_link_libraries(ant-system-bin
        ant-system
        nearest-neighbour
        libraries
        ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(ant-system-bin
        PROPERTIES OUTPUT_NAME ant-system)
