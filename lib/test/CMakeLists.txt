enable_testing()
add_executable(suso_test suso_test.cpp)

add_dependencies(suso_test gtest)

target_include_directories(suso_test PRIVATE
        ${PROJECT_SOURCE_DIR}/lib/include
        ${GTEST_SOURCE_DIR}/googletest/include
        ${GTEST_SOURCE_DIR}/googlemock/include)

target_link_libraries(suso_test
        suso
        pthread
        ${GTEST_BINARY_DIR}/googlemock/gtest/libgtest.a
        ${GTEST_BINARY_DIR}/googlemock/gtest/libgtest_main.a)

add_test(NAME susoUnitTest COMMAND suso_test)
