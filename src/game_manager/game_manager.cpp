#include "game_manager.hpp"

#include <exception>
#include <string>
#include "mine_field_builder.hpp"
#include "log_macro.hpp"

namespace game_manager {
GameManager::GameManager(std::shared_ptr<interact::CommandReader> command_reader,
                         std::shared_ptr<logger::Logger> logger,
                         std::shared_ptr<renderer::Renderer> renderer) : command_reader_(command_reader),
                                                                     logger_(logger),
                                                                     renderer_(renderer),
                                                                     ui_manager_(std::make_shared<ui::UIManager>(renderer_, logger_)) {
  LOG("GameManager initialized");
  // command_reader_->SetLogger(logger_);
  
  global_type::ReturnStruct ret_stt;
  ret_stt = command_reader_->RegisterCommandHandler(std::bind(&GameManager::GameCommand, this, std::placeholders::_1));
  if (ret_stt.state_ == global_type::ReturnState::OK) {
    command_reader_->StartCommandReading();
  }
}


// hnu5hc todo: re-factor this method
global_type::ReturnStruct GameManager::GameCommand(const std::string& command) {
  LOG("GameManager::GameCommand() called with string: " << command);
  if (command == "exit") {
    command_reader_->StopCommandReading();
    return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
  }

  std::vector<std::string> command_arg = ExtractCommandArg(command);
  if (command_arg.size() == 0) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK};
  }

  return ui_manager_->FeedCommand(command_arg);
  
  // std::cout << "command lenght: " << command_arg.size() << std::endl;
  // std::cout << "Got command elements as following:" << std::endl;
  // int count = 0;
  // for (auto& it : command_arg) {
  //   std::cout << count << " : " << it << std::endl;
  //   count++;
  // }
  // return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

std::string GameManager::PreProcessingCommand(const std::string& command) {
  std::string ret = command;
  auto itr = ret.begin();
  while ((*itr) == ' ') {
    ret.erase(itr);
  }
  for (auto it = ret.begin(); it != ret.end(); it++) {
    if ((*it) == ' ') {
      while (((*it) == ' ') && ((*(it + 1)) == ' ')) {
        ret.erase(it);
      }
    }
  }
  if (*(ret.end()-1) == ' ') {ret.erase(ret.end()-1);}
  return ret;
}

std::vector<std::string> GameManager::ExtractCommandArg(const std::string& command) {
  std::string final_command = PreProcessingCommand(command);
  std::vector<std::string> ret_vec{};
  while (final_command != "") {
    std::size_t first_space_char_pos = final_command.find_first_of(' ');
    if (first_space_char_pos != std::string::npos) {
      std::string command_section = final_command.substr(0, first_space_char_pos);
      ret_vec.push_back(command_section);
      final_command = final_command.substr(first_space_char_pos + 1);
    } else {
      ret_vec.push_back(final_command);
      final_command = "";
    }
  }
  return ret_vec;
}
} // namespace game_manager
