cmake_minimum_required(VERSION 3.5)

project(SudokuSolver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(app)

enable_testing()
