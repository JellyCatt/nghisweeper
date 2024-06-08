cmake_minimum_required(VERSION 3.10)

add_library(Renderer console_renderer.cpp)
target_include_directories(Renderer PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(Renderer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Renderer PUBLIC 
                                      MineField
                                      Logger
)
