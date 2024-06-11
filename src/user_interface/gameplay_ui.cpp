#include "gameplay_ui.hpp"

#include <memory>
#include <functional>

#include "log_macro.hpp"

namespace ui {
GameplayUI::GameplayUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger,
     std::map<std::string,std::string> init_info) : UI(renderer, logger, init_info),
                                                    mine_field_builder_(std::make_shared<mine_field::MineFieldBuilder>()),
                                                    local_mine_field_(nullptr),
                                                    local_hint_and_help_(std::map<std::string,std::string>{}),
                                                    ui_execute_map_{} {
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("R", std::bind(&GameplayUI::CommandReveal, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("r", std::bind(&GameplayUI::CommandReveal, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("S", std::bind(&GameplayUI::CommandSmartReveal, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("s", std::bind(&GameplayUI::CommandSmartReveal, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("Q", std::bind(&GameplayUI::CommandQuestion, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("q", std::bind(&GameplayUI::CommandQuestion, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("F", std::bind(&GameplayUI::CommandFlag, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("f", std::bind(&GameplayUI::CommandFlag, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("-R", std::bind(&GameplayUI::CommandRestart, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("-r", std::bind(&GameplayUI::CommandRestart, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("-N", std::bind(&GameplayUI::CommandNewGame, this, std::placeholders::_1)));
  ui_execute_map_.emplace(std::pair<std::string,RoutingFunc>("-n", std::bind(&GameplayUI::CommandNewGame, this, std::placeholders::_1)));
  InitNewGame(init_info);
}

global_type::ReturnStruct GameplayUI::FeedCommand(const std::vector<std::string>& command) {
  // the first element of vector will be the command for MainMenu UI
  LOG("MainMenuUI::FeedCommand() A command has been feed to MainMenu UI ");
  global_type::ReturnStruct ret;

  std::string choice = *(command.begin());
  auto execute_it = ui_execute_map_.find(choice);
  if (execute_it != ui_execute_map_.end()) {
    ret = execute_it->second(command);
  } else {
    ret = CommandOther(command);
  }
  local_hint_and_help_.emplace("99", "---HINTs---");
  RenderUI();
  return ret;
}

global_type::ReturnStruct GameplayUI::RenderUI() {
  std::map<std::string,std::string> user_options{};
  user_options.emplace("R <row> <col>","Reveal");
  user_options.emplace("S <row> <col>","Smart Reveal");
  user_options.emplace("Q <row> <col>","Question");
  user_options.emplace("F <row> <col>","Flag");
  user_options.emplace("-R","Restart");
  user_options.emplace("-N C <row> <col> <num>","New game with custom difficulty");
  user_options.emplace("-N D <difficulty>","New game with pre-defined difficulty");
  

  renderer::RenderRequest::AdditionalInfoType add_info{};
  add_info.emplace("hint_and_help", local_hint_and_help_);
  add_info.emplace("user_options", user_options);
  renderer::RenderRequest new_request(local_mine_field_, add_info);

  renderer_->Render(new_request);
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

mine_field::Difficulty GameplayUI::ParseDifficulty(const std::string& diff_string) {
  if (diff_string == "easy") return mine_field::Difficulty::EASY;
  if (diff_string == "medium") return mine_field::Difficulty::MEDIUM;
  if (diff_string == "hard") return mine_field::Difficulty::HARD;
  return mine_field::Difficulty::EASY;
}

global_type::ReturnStruct GameplayUI::InitNewGame(std::map<std::string,std::string> init_info) {
  LOG("GameplayUI::InitNewGame(std::map<std::string,std::string> init_info) called");
  auto diff_it = init_info.find("difficulty");
  if (diff_it == init_info.end()) {
    LOG("GameplayUI::InitNewGame() there is no difficulty information, init as EASY mode...");
    return InitNewGame(mine_field::Difficulty::EASY);
  } else {
    return InitNewGame(diff_it->second);
  }
}


global_type::ReturnStruct GameplayUI::InitNewGame(const std::string& diff_string) {
  if (diff_string == "easy") {
    return InitNewGame(mine_field::Difficulty::EASY);
  }
  if (diff_string == "medium") {
    return InitNewGame(mine_field::Difficulty::MEDIUM);
  }
  if (diff_string == "hard") {
    return InitNewGame(mine_field::Difficulty::HARD);
  }
  return InitNewGame(mine_field::Difficulty::EASY);
}

global_type::ReturnStruct GameplayUI::InitNewGame(mine_field::Difficulty diff) {
  local_mine_field_ = mine_field_builder_->GetMineField(diff);
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

static uint16_t ExtractInteger(const std::string& input) {
  uint16_t ret_val;
  try {
    ret_val = std::stoi(input);
  } catch (const std::exception& e) {
    ret_val = 9999;
  }
  return 9999;
}

mine_field::Position GameplayUI::ExtractPosition(const std::vector<std::string> command) {
  if (command.size() < 3) return mine_field::Position{.row_=9999,.col_=9999};
  uint16_t row = ExtractInteger(command[1]);
  uint16_t col = ExtractInteger(command[2]);
  return mine_field::Position{.row_=row,.col_=col};
}

global_type::ReturnStruct GameplayUI::CommandFlag(const std::vector<std::string> command) {
  return local_mine_field_->Flag(ExtractPosition(command));
}

global_type::ReturnStruct GameplayUI::CommandQuestion(const std::vector<std::string> command) {
  return local_mine_field_->Question(ExtractPosition(command));
}

global_type::ReturnStruct GameplayUI::CommandReveal(const std::vector<std::string> command) {
  return local_mine_field_->Reveal(ExtractPosition(command));
}

global_type::ReturnStruct GameplayUI::CommandSmartReveal(const std::vector<std::string> command) {
  return local_mine_field_->SmartReveal(ExtractPosition(command));
}

global_type::ReturnStruct GameplayUI::CommandRestart(const std::vector<std::string> command) {
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}
global_type::ReturnStruct GameplayUI::CommandNewGame(const std::vector<std::string> command) {
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}

global_type::ReturnStruct GameplayUI::CommandOther(const std::vector<std::string> command) {
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK};
}
} // namespace ui
