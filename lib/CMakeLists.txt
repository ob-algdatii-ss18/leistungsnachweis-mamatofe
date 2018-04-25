add_library (suso src/suso.cpp include/suso.h)
target_include_directories(suso PRIVATE include)

enable_testing()
add_subdirectory(test)
