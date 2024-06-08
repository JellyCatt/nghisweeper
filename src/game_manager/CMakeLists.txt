cmake_minimum_required(VERSION 3.10)

add_library(GameManager game_manager.cpp)
target_include_directories(GameManager PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(GameManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GameManager PUBLIC 
                                          MineField
                                          Renderer
                                          GlobalType
                                          ConsoleReader
                                          Logger
                                          UserInterface
)
