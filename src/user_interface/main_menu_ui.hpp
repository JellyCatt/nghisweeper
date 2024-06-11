#ifndef MAIN_MENU_UI_HPP
#define MAIN_MENU_UI_HPP

#include "ui.hpp"

#include <map>
#include <functional>

namespace ui {
class MainMenuUI : public UI {
public:
  MainMenuUI(std::shared_ptr<renderer::Renderer> renderer,
             std::shared_ptr<logger::Logger> logger,
             std::map<std::string,std::string> init_info);
  global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command) override;
  global_type::ReturnStruct RenderUI() override;

private:
  global_type::ReturnStruct ExecuteNewGame();
  global_type::ReturnStruct ExecuteHelp();
  global_type::ReturnStruct ExecuteExit();
  global_type::ReturnStruct ExecuteOther();

  std::map<std::string,std::string> local_hint_and_help_;
  std::map<std::string,std::function<global_type::ReturnStruct(void)>> ui_execute_map_;
};
/* Brief appearance
---MAIN MENU---
1. New Game
2. Help
3. Exit
---------------
Please make your choice by inputing number + ENTER key
->
*/
} // namespace ui


#endif // MAIN_MENU_UI_HPP