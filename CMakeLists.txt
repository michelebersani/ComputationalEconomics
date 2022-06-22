cmake_minimum_required(VERSION 3.10)
project(CellularAutomata VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O3 -finline-functions -DNDEBUG -I -g -pthread")

add_library(
    thread_solver
    ../code/solvers.h
    ../code/solver_thread.cpp
)
add_library(
    board
    ../code/board.h
    ../code/board.cpp
)
add_library(
    rules
    ../code/rules.h
    ../code/rules.cpp
)

add_executable(thread ../code/game_of_life_thread.cpp)
target_link_libraries(thread PRIVATE thread_solver rules board)