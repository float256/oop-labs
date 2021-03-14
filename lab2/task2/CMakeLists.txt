cmake_minimum_required(VERSION 3.17)
project(task2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(HtmlDecoder)
add_subdirectory(Tests)

add_executable(task2 main.cpp)

target_link_libraries("${PROJECT_NAME}" html-decoder-library)
