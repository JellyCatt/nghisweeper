#include <signal.h>
#include <iostream>
#include <memory>

#include "game_manager.hpp"
#include "console_reader.hpp"
#include "console_renderer.hpp"
#include "file_logger.hpp"

int main() {
  std::cout << "This is main :)" << std::endl;
  auto my_file_logger = std::make_shared<logger::FileLogger>();
  auto my_console_reader = std::make_shared<interact::ConsoleCommandReader>();
  my_console_reader->SetLogger(my_file_logger);
  auto my_console_renderer = std::make_shared<renderer::ConsoleRenderer>();
  my_console_renderer->SetLogger(my_file_logger);

  auto my_game_manager = std::make_shared<game_manager::GameManager>(my_console_reader, my_file_logger, my_console_renderer);
  return 0;
}