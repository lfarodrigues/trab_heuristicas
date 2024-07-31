cmake_minimum_required(VERSION 3.26)
project(trab_heuristicas)

set(CMAKE_CXX_STANDARD 14)

include_directories(metaheuristic)

add_executable(trab_heuristicas
        metaheuristic/item.cpp
        metaheuristic/item.h
        metaheuristic/knapsack.cpp
        metaheuristic/knapsack.h
        metaheuristic/main.cpp
        metaheuristic/simulated_annealing.cpp
        metaheuristic/simulated_annealing.h)
