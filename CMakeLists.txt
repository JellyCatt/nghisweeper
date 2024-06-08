cmake_minimum_required(VERSION 3.10)
project(LATTICE_FIL_PLUGIN VERSION 1.0)


add_subdirectory(src/console_reader)
add_subdirectory(src/game_manager)
add_subdirectory(src/global_header)
add_subdirectory(src/logger)
add_subdirectory(src/mine_field_object)
add_subdirectory(src/renderer)
add_subdirectory(src/user_interface)
add_subdirectory(src/utils)


add_executable(minesweeper src/main.cpp)
target_include_directories(minesweeper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(minesweeper PRIVATE
  Renderer
  GameManager
  MineField
  Utils
  GlobalType
  ConsoleReader
  Logger
)
