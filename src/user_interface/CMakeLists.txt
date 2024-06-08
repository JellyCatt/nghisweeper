cmake_minimum_required(VERSION 3.10)

add_library(UserInterface ui_manager.cpp main_menu_ui.cpp)
target_include_directories(UserInterface PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(UserInterface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(UserInterface PUBLIC 
                                            Logger
                                            Renderer
                                            GlobalType
)
