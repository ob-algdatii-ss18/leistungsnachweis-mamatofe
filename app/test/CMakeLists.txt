enable_testing()
add_executable(soduko_test sodukotest.cpp)

add_dependencies(soduko_test gtest)
include_directories(${source_dir}/googletest/include
        ${source_dir}/googlemock/include)

target_link_libraries(soduko_test pthread)
target_link_libraries(soduko_test ${binary_dir}/googlemock/gtest/libgtest.a)
target_link_libraries(soduko_test ${binary_dir}/googlemock/gtest/libgtest_main.a)

add_test(NAME sudoku-solverTest COMMAND soduko_test)
