#ifndef GAMEPLAY_UI_HPP
#define GAMEPLAY_UI_HPP

#include "ui.hpp"

namespace ui {
class GameplayUI : public UI {
public:
  GameplayUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger,
     std::map<std::string,std::string> init_info) : UI(renderer, logger, init_info) {}
  global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command) override { return global_type::ReturnStruct{global_type::ReturnState::OK}; }
  global_type::ReturnStruct RenderUI() override { return global_type::ReturnStruct{global_type::ReturnState::OK}; }
};
} // namespace ui


#endif // GAMEPLAY_UI_HPP