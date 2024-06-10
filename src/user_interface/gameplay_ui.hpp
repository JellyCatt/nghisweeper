#ifndef GAMEPLAY_UI_HPP
#define GAMEPLAY_UI_HPP

#include "ui.hpp"

#include <memory>
#include <map>
#include "mine_field_builder.hpp"
#include "mine_field_object.hpp"

namespace ui {
class GameplayUI : public UI {
public:
  GameplayUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger,
     std::map<std::string,std::string> init_info);
  global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command) override;
  global_type::ReturnStruct RenderUI() override { return global_type::ReturnStruct{global_type::ReturnState::OK}; }

private:
  mine_field::Difficulty ParseDifficulty(const std::string& diff_string);

  global_type::ReturnStruct InitNewGame(const std::string& diff_string) {}
  global_type::ReturnStruct InitNewGame(mine_field::Difficulty& diff) {}

  std::shared_ptr<mine_field::MineField> local_mine_field_;
  std::shared_ptr<mine_field::MineFieldBuilder> mine_field_builder_;
};
} // namespace ui


#endif // GAMEPLAY_UI_HPP