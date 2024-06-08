cmake_minimum_required(VERSION 3.10)

add_library(GlobalType INTERFACE)
target_include_directories(GlobalType INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})