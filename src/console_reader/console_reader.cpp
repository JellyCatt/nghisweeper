#include "console_reader.hpp"
#include <iostream>
#include "log_macro.hpp"

namespace interact {
ConsoleCommandReader::ConsoleCommandReader() : is_running_(true), command_callback_(nullptr) {
  
}

global_type::ReturnStruct ConsoleCommandReader::RegisterCommandHandler(CommandReaderCallbackType callback) {
  LOG("ConsoleCommandReader::RegisterCommandHandler() callback registered");
  command_callback_ = callback;
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct ConsoleCommandReader::StartCommandReading() {
  LOG("ConsoleCommandReader::StartCommandReading() called");
  this->ReaderLoop();
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct ConsoleCommandReader::StopCommandReading() {
  LOG("ConsoleCommandReader::StopCommandReading() called");
  this->Terminate();
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

void ConsoleCommandReader::ReaderLoop() {
  while (is_running_) {
    LOG("ConsoleCommandReader::ReaderLoop() Reader while loop")
    std::string input_string;
    std::getline(std::cin, input_string);
    if (command_callback_ != nullptr) {
      auto call_stt = command_callback_(input_string);
      if (call_stt.state_ != global_type::ReturnState::OK) {
        LOG("ReaderLoop() callback call failed: " << call_stt.info_);
      }
      
    }
  }
}

void ConsoleCommandReader::Terminate() {
  is_running_ = false;
}
} // namespace interact
