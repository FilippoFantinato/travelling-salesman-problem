cmake_minimum_required(VERSION 3.10)

include_directories(${CPLEX_INC_DIR})

add_library(tsp-solvers
        TSPCPXSolver.h
        TSPCPXSolver.cpp
        TSPSolver.h
        TSPSolver.cpp
        cpxmacro.h
        )
