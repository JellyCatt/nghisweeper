#ifndef DIFFICULTY_UI_HPP
#define DIFFICULTY_UI_HPP

#include "ui.hpp"

namespace ui {
class DifficultyUI : public UI {
public:
  DifficultyUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger) : UI(renderer, logger) {}
  global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command) override { return global_type::ReturnStruct{global_type::ReturnState::OK}; }
  global_type::ReturnStruct RenderUI() override { return global_type::ReturnStruct{global_type::ReturnState::OK}; }
};
} // namespace ui


#endif // DIFFICULTY_UI_HPP