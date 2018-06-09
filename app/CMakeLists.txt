add_executable(sudoku-solver src/main.cpp)

add_dependencies(sudoku-solver args)

target_include_directories(sudoku-solver PRIVATE
        ${PROJECT_SOURCE_DIR}/lib/include
        ${ARGS_SOURCE_DIR})

target_link_libraries(sudoku-solver suso)

enable_testing()
add_subdirectory(test)
