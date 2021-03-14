cmake_minimum_required(VERSION 3.17)
project(TaskOne)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(VectorProcessing)
add_subdirectory(Tests)

add_executable(TaskOne main.cpp)

target_link_libraries("${PROJECT_NAME}" vector-processing-library)
