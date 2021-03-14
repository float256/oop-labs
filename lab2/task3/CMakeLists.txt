cmake_minimum_required(VERSION 3.17)
project(task3)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(EratostheneSieve)
add_subdirectory(Tests)

add_executable("${PROJECT_NAME}" main.cpp)

target_link_libraries("${PROJECT_NAME}" eratosthene-sieve-library)
