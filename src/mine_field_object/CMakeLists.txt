cmake_minimum_required(VERSION 3.10)

add_library(MineField mine_field_object.cpp mine_field_builder.cpp)
target_include_directories(MineField PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(MineField INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MineField PUBLIC 
                                        Utils
                                        Logger
)
