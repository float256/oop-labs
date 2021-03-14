cmake_minimum_required(VERSION 3.17)
project(TaskTwo_Tests)

set(CMAKE_CXX_STANDARD 11)

add_executable(TaskTwo_Tests HtmlDecoderTests)

target_link_libraries("${PROJECT_NAME}" html-decoder-library)
