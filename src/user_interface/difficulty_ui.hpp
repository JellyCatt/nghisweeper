#ifndef DIFFICULTY_UI_HPP
#define DIFFICULTY_UI_HPP

#include "ui.hpp"

#include <map>
#include <string>

namespace ui {
class DifficultyUI : public UI {
public:
  DifficultyUI(std::shared_ptr<renderer::Renderer> renderer,
     std::shared_ptr<logger::Logger> logger,
     std::map<std::string,std::string> init_info);
  global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command);
  global_type::ReturnStruct RenderUI() override;

private:
  global_type::ReturnStruct SelectEasy();
  global_type::ReturnStruct SelectMedium();
  global_type::ReturnStruct SelectHard();
  global_type::ReturnStruct SelectBack();
  global_type::ReturnStruct SelectExit();
  global_type::ReturnStruct SelectOther();

  std::map<std::string,std::string> local_hint_and_help_;
};
/* Brief appearance
---DIFFICULTY SELECT---
1. Easy
2. Medium
3. Hard
4. Back to Main Menu
5. Exit
---------------
*/
} // namespace ui


#endif // DIFFICULTY_UI_HPP