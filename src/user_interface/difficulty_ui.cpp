#include "difficulty_ui.hpp"

#include "log_macro.hpp"
namespace ui {
DifficultyUI::DifficultyUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger,
     std::map<std::string,std::string> init_info) : UI(renderer, logger, init_info), local_hint_and_help_{} {
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("1", std::bind(&DifficultyUI::SelectEasy, this)));
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("2", std::bind(&DifficultyUI::SelectMedium, this)));
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("3", std::bind(&DifficultyUI::SelectHard, this)));
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("4", std::bind(&DifficultyUI::SelectBack, this)));
  ui_execute_map_.emplace(std::pair<std::string,std::function<global_type::ReturnStruct(void)>>("5", std::bind(&DifficultyUI::SelectExit, this)));  
}

global_type::ReturnStruct DifficultyUI::FeedCommand(const std::vector<std::string>& command) {
  LOG("DifficultyUI::FeedCommand() A command has been feed to MainMenu UI ");
  global_type::ReturnStruct ret;

  std::string choice = *(command.begin());
  auto execute_it = ui_execute_map_.find(choice);
  if (execute_it != ui_execute_map_.end()) {
    ret = execute_it->second();
  } else {
    ret = SelectOther();
  }

  local_hint_and_help_.emplace("99", "---DIFFICULTY SELECT---");
  RenderUI();
  return ret;
}

global_type::ReturnStruct DifficultyUI::RenderUI() {
  std::map<std::string,std::string> user_options{};
  user_options.emplace("1","Easy");
  user_options.emplace("2","Medium");
  user_options.emplace("3","Hard");
  user_options.emplace("4","Back to Main Menu");
  user_options.emplace("5","Exit Game");

  renderer::RenderRequest::AdditionalInfoType add_info{};
  add_info.emplace("hint_and_help", local_hint_and_help_);
  add_info.emplace("user_options", user_options);
  renderer::RenderRequest new_request(nullptr, add_info);

  renderer_->Render(new_request);
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct DifficultyUI::SelectEasy() {
  local_hint_and_help_.clear();
  LOG("Easy selected");
  local_hint_and_help_.emplace("1", "You choose EASY, be ready :)");
  // todo: do something more to change ui
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct DifficultyUI::SelectMedium() {
  local_hint_and_help_.clear();
  LOG("Easy selected");
  local_hint_and_help_.emplace("1", "You choose MEDIUM, be ready :)");
  // todo: do something more to change ui
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct DifficultyUI::SelectHard() {
  local_hint_and_help_.clear();
  LOG("Easy selected");
  local_hint_and_help_.emplace("1", "You choose HARD, be ready :)");
  // todo: do something more to change ui
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct DifficultyUI::SelectBack() {
  local_hint_and_help_.clear();
  LOG("Easy selected");
  local_hint_and_help_.emplace("1", "You choose BACK TO MAIN MENU, backing...");
  
  current_state_ = UI::UIState::END;
  next_session_ = ui::UISession::MAIN_MENU;
  
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct DifficultyUI::SelectExit() {
  local_hint_and_help_.clear();
  LOG("Easy selected");
  local_hint_and_help_.emplace("1", "You choose EXIT? Oh no...");
  // todo: do something more to change ui
  return global_type::ReturnStruct{.state_=global_type::ReturnState::TERMINATED};
}

global_type::ReturnStruct DifficultyUI::SelectOther() {
  local_hint_and_help_.clear();
  LOG("Easy selected");
  local_hint_and_help_.emplace("1", "Stop choosing nonsense :)");
  // todo: do something more to change ui
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}
} // namespace ui
