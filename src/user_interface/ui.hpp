#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <string>
#include <memory>
#include <map>
#include <functional>

#include "file_logger.hpp"
#include "global_type.hpp"
#include "logger.hpp"
#include "renderer.hpp"

namespace ui {
enum class UISession {
  MAIN_MENU,
  DIFFICULTY_SELECT,
  GAME_PLAY,
  UNKNOWN
};
class UI {
public:
  enum class UIState {
    IN_OPERATE,
    END,
    UNKNOWN
  };
  UI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger) : renderer_(renderer),
                                               logger_(logger),
                                               current_state_(UIState::IN_OPERATE),
                                               next_session_(UISession::UNKNOWN),
                                               next_session_info_{} {}

  virtual global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command) = 0;
  virtual global_type::ReturnStruct RenderUI() = 0;

  UIState GetCurrentState() const { return current_state_; }
  UISession GetNextSession() const { return next_session_; }
  std::map<std::string,std::string> GetNextSessionInfo() { return next_session_info_; }

protected:
  UIState current_state_;
  UISession next_session_;
  std::map<std::string,std::string> next_session_info_;
  std::shared_ptr<renderer::Renderer> renderer_;
  std::shared_ptr<logger::Logger> logger_;
  std::map<std::string,std::function<global_type::ReturnStruct(void)>> ui_execute_map_;

};
} // namespace user_interface

#endif // USER_INTERFACE_HPP