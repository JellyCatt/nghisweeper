#include "ui_manager.hpp"

#include <memory>

#include "main_menu_ui.hpp"
#include "difficulty_ui.hpp"
#include "gameplay_ui.hpp"

namespace ui {
UIManager::UIManager(std::shared_ptr<renderer::Renderer> renderer,
                     std::shared_ptr<logger::Logger> logger) : renderer_(renderer),
                                                               logger_(logger),
                                                               current_ui_(std::make_shared<MainMenuUI>(renderer_, logger_,
                                                               std::map<std::string, std::string>{})) {}

global_type::ReturnStruct UIManager::FeedCommand(const std::vector<std::string>& command) {
  if (current_ui_ == nullptr) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,
                                     .info_="No UI is currently in session..."};
  }

  auto ret = current_ui_->FeedCommand(command);
  if (ret.state_ != global_type::ReturnState::OK) {
    return ret;
  }

  if (current_ui_->GetCurrentState() == UI::UIState::END) {
    return InitNextUI(current_ui_->GetNextSession(), current_ui_->GetNextSessionInfo());
  }
  return ret;
}

global_type::ReturnStruct UIManager::InitNextUI(UISession next_session, std::map<std::string, std::string> next_session_info) {
  global_type::ReturnStruct ret;
  switch (next_session) {
  case UISession::MAIN_MENU:
    ret.state_ = global_type::ReturnState::OK;
    current_ui_ = std::make_shared<ui::MainMenuUI>(renderer_, logger_, next_session_info);
    break;
  case UISession::DIFFICULTY_SELECT:
    ret.state_ = global_type::ReturnState::OK;
    current_ui_ = std::make_shared<ui::DifficultyUI>(renderer_, logger_, next_session_info);
    break;
  case UISession::GAME_PLAY:
    ret.state_ = global_type::ReturnState::OK;
    current_ui_ = std::make_shared<ui::GameplayUI>(renderer_, logger_, next_session_info);
    break;
  case UISession::UNKNOWN:
    ret.state_ = global_type::ReturnState::NOT_OK;
    ret.info_ = "UNKNOWN next session...";
    current_ui_ = nullptr;
    break;
  default:
    ret.state_ = global_type::ReturnState::NOT_OK;
    ret.info_ = "System fallen into UNKNOWN session...";
    current_ui_ = nullptr;
    break;
  }
  return ret;
}
} // namespace ui
