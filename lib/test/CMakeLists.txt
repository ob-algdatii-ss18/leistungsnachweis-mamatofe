enable_testing()
add_executable(sudoku_test sudokutest.cpp)

add_dependencies(sudoku_test gtest)
target_include_directories(sudoku_test PRIVATE ${source_dir}/googletest/include
        ${source_dir}/googlemock/include)

target_link_libraries(sudoku_test pthread)
target_link_libraries(sudoku_test ${binary_dir}/googlemock/gtest/libgtest.a)
target_link_libraries(sudoku_test ${binary_dir}/googlemock/gtest/libgtest_main.a)

add_test(NAME sudoku-solverUnitTest COMMAND sudoku_test)
