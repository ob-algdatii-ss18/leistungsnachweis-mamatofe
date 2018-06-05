add_library (suso src/suso.cpp include/suso.h)
target_include_directories(suso PRIVATE ${PROJECT_SOURCE_DIR}/lib/include)

enable_testing()
add_subdirectory(test)
