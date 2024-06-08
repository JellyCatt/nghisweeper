#ifndef FLOW_HANDLER_HPP
#define FLOW_HANDLER_HPP

#include <memory>
#include <string>
#include <functional>
#include <vector>

#include "global_type.hpp"
#include "mine_field_object.hpp"
#include "console_renderer.hpp"
#include "console_reader.hpp"
#include "logger.hpp"
#include "ui_manager.hpp"

namespace game_manager {
enum class GameState {
  PRE_START,
  ON_GOING,
  END
};

class GameManager {
public:
  GameManager(std::shared_ptr<interact::CommandReader> command_reader,
              std::shared_ptr<logger::Logger> logger,
              std::shared_ptr<renderer::Renderer> renderer);

  global_type::ReturnStruct GameCommand(const std::string& command);
  void SetLogger(std::shared_ptr<logger::Logger> logger) { logger_ = logger; }
  
private:
  std::string PreProcessingCommand(const std::string& command);
  std::vector<std::string> ExtractCommandArg(const std::string& command);

  std::shared_ptr<interact::CommandReader> command_reader_;
  std::shared_ptr<logger::Logger> logger_;
  std::shared_ptr<renderer::Renderer> renderer_;
  
  std::shared_ptr<ui::UIManager> ui_manager_;
};
} // namespace game_manager
#endif // FLOW_HANDLER_HPP