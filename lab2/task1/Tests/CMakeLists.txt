cmake_minimum_required(VERSION 3.17)
project(TaskOne_Tests)

set(CMAKE_CXX_STANDARD 11)

add_executable(TaskOne_Tests VectorProcessingTests.cpp)

target_link_libraries("${PROJECT_NAME}" vector-processing-library)
