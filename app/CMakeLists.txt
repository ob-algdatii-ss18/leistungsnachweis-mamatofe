add_executable(sudoku-solver src/main.cpp)
target_include_directories(sudoku-solver PRIVATE ${PROJECT_SOURCE_DIR}/lib/include)
target_link_libraries(sudoku-solver suso)

enable_testing()
add_subdirectory(test)
