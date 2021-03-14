cmake_minimum_required(VERSION 3.17)
project(TaskThree_Tests)

set(CMAKE_CXX_STANDARD 11)

add_executable(TaskThree_Tests EratostheneSieveTests.cpp)

target_link_libraries("${PROJECT_NAME}" eratosthene-sieve-library)
