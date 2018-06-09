cmake_minimum_required(VERSION 3.5)

project(SudokuSolver)

include(ExternalProject)
ExternalProject_Add(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest SOURCE_DIR BINARY_DIR)
set(GTEST_SOURCE_DIR ${SOURCE_DIR})
set(GTEST_BINARY_DIR ${BINARY_DIR})

ExternalProject_Add(args
    GIT_REPOSITORY https://github.com/Taywee/args.git
    GIT_TAG 6.2.0
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/args
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(args SOURCE_DIR BINARY_DIR)
set(ARGS_SOURCE_DIR ${SOURCE_DIR})
set(ARGS_BINARY_DIR ${BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Valgrind
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
endif()

add_subdirectory(lib)
add_subdirectory(app)

include(CTest)
enable_testing()
