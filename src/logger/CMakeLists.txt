cmake_minimum_required(VERSION 3.10)

add_library(Logger file_logger.cpp)
target_include_directories(Logger PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(Logger INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
