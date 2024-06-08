#include "main_menu_ui.hpp"

#include <map>
#include <functional>
#include <string>

#include "log_macro.hpp"
#include "renderer.hpp"

namespace ui {
MainMenuUI::MainMenuUI(std::shared_ptr<renderer::Renderer> renderer,
             std::shared_ptr<logger::Logger> logger) : UI(renderer, logger), local_hint_and_help_{} {
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("1", std::bind(&MainMenuUI::ExecuteNewGame, this)));
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("2", std::bind(&MainMenuUI::ExecuteHelp, this)));
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("0", std::bind(&MainMenuUI::ExecuteExit, this)));
}

global_type::ReturnStruct MainMenuUI::FeedCommand(const std::vector<std::string>& command) {
  // the first element of vector will be the command for MainMenu UI
  std::string choice = *(command.begin());
  auto execute_it = ui_execute_map_.find(choice);
  if (execute_it != ui_execute_map_.end()) {
    return execute_it->second();
  } else {
    local_hint_and_help_.clear();
    local_hint_and_help_.emplace("1", "Stop messing around please :)");
    return RenderUI();
  }
}

global_type::ReturnStruct MainMenuUI::RenderUI() {
  std::map<std::string,std::string> user_options{};
  user_options.emplace("1","New Game");
  user_options.emplace("2","Help");
  user_options.emplace("3","Exit");

  renderer::RenderRequest::AdditionalInfoType add_info{};
  add_info.emplace("hint_and_help", local_hint_and_help_);
  add_info.emplace("user_options", user_options);
  renderer::RenderRequest new_request(nullptr, add_info);

  renderer_->Render(new_request);
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct MainMenuUI::ExecuteNewGame() {
  local_hint_and_help_.clear();
  LOG("ExecuteNewGame called");
  local_hint_and_help_.emplace("1", "Main Menu chosen, please wait some time to start game :)");
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct MainMenuUI::ExecuteHelp() {
  local_hint_and_help_.clear();
  LOG("ExecuteHelp called");
  local_hint_and_help_.emplace("1", "Google it and learn by yourself :)");
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct MainMenuUI::ExecuteExit() {
  local_hint_and_help_.clear();
  LOG("ExecuteExit called");
  local_hint_and_help_.emplace("1", "I will die and you cannot see it");
  return global_type::ReturnStruct{.state_=global_type::ReturnState::TERMINATED};
}
} // namespace ui