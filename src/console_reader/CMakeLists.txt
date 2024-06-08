cmake_minimum_required(VERSION 3.10)

add_library(ConsoleReader console_reader.cpp)
target_include_directories(ConsoleReader PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(ConsoleReader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ConsoleReader PUBLIC 
                                            GlobalType
                                            Logger
)
