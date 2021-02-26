cmake_minimum_required(VERSION 3.0.0)
project(Lab1Invert VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(LinearAlgebra)
add_executable(Lab1Invert main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries("${PROJECT_NAME}" LinearAlgebraLibrary)