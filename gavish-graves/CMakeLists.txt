cmake_minimum_required(VERSION 3.10)

add_library(gavish-graves
        GavishGraves.h
        GavishGraves.cpp)

add_executable(gavish-graves-bin main.cpp)
target_link_libraries(gavish-graves-bin
        gavish-graves
        libraries
        ${cplex_libraries}
        ${CMAKE_THREAD_LIBS_INIT}
        ${CMAKE_DL_LIBS})
set_target_properties(gavish-graves-bin
        PROPERTIES OUTPUT_NAME gavish-graves)
