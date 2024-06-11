#ifndef GAMEPLAY_UI_HPP
#define GAMEPLAY_UI_HPP

#include "ui.hpp"

#include <memory>
#include <map>
#include <functional>
#include "mine_field_builder.hpp"
#include "mine_field_object.hpp"

namespace ui {
class GameplayUI : public UI {
using RoutingFunc=std::function<global_type::ReturnStruct(const std::vector<std::string>)>;
public:
  GameplayUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger,
     std::map<std::string,std::string> init_info);
  global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command) override;
  global_type::ReturnStruct RenderUI() override;

private:
  mine_field::Difficulty ParseDifficulty(const std::string& diff_string);

  global_type::ReturnStruct InitNewGame(std::map<std::string,std::string> init_info);
  global_type::ReturnStruct InitNewGame(const std::string& diff_string);
  global_type::ReturnStruct InitNewGame(mine_field::Difficulty diff);

  mine_field::Position ExtractPosition(const std::vector<std::string> command);
  uint16_t ExtractInteger(const std::string& input);

  global_type::ReturnStruct CommandFlag(const std::vector<std::string> command);
  global_type::ReturnStruct CommandQuestion(const std::vector<std::string> command);
  global_type::ReturnStruct CommandReveal(const std::vector<std::string> command);
  global_type::ReturnStruct CommandSmartReveal(const std::vector<std::string> command);
  global_type::ReturnStruct CommandRestart(const std::vector<std::string> command);
  global_type::ReturnStruct CommandNewGame(const std::vector<std::string> command);
  global_type::ReturnStruct CommandOther(const std::vector<std::string> command);

  std::shared_ptr<mine_field::MineField> local_mine_field_;
  std::shared_ptr<mine_field::MineFieldBuilder> mine_field_builder_;
  std::map<std::string,std::string> local_hint_and_help_;
  std::map<std::string,RoutingFunc> ui_execute_map_;
};
} // namespace ui


#endif // GAMEPLAY_UI_HPP