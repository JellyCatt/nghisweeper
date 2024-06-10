#include "gameplay_ui.hpp"

#include <memory>

#include "log_macro.hpp"

namespace ui {
GameplayUI::GameplayUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger,
     std::map<std::string,std::string> init_info) : UI(renderer, logger, init_info),
                                                    mine_field_builder_(std::make_shared<mine_field::MineFieldBuilder>()),
                                                    local_mine_field_(nullptr) {
  InitNewGame(init_info["difficulty"]);
}

global_type::ReturnStruct GameplayUI::FeedCommand(const std::vector<std::string>& command) {
  // the first element of vector will be the command for MainMenu UI
  LOG("MainMenuUI::FeedCommand() A command has been feed to MainMenu UI ");
  global_type::ReturnStruct ret;

  std::string choice = *(command.begin());
  auto execute_it = ui_execute_map_.find(choice);
  if (execute_it != ui_execute_map_.end()) {
    ret = execute_it->second();
  } else {
    // ret = ExecuteOther();
  }
  // local_hint_and_help_.emplace("99", "---MAIN MENU---");
  RenderUI();
  return ret;
}
} // namespace ui
