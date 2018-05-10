enable_testing()
add_executable(suso_test suso_test.cpp)

add_dependencies(suso_test gtest)

target_include_directories(suso_test PRIVATE ${PROJECT_SOURCE_DIR}/lib/include)
target_include_directories(suso_test PRIVATE ${source_dir}/googletest/include
        ${source_dir}/googlemock/include)

target_link_libraries(suso_test suso)
target_link_libraries(suso_test pthread)
target_link_libraries(suso_test ${binary_dir}/googlemock/gtest/libgtest.a)
target_link_libraries(suso_test ${binary_dir}/googlemock/gtest/libgtest_main.a)

add_test(NAME susoUnitTest COMMAND suso_test)
