#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <string>
#include <memory>
#include <vector>

#include "logger.hpp"
#include "renderer.hpp"
#include "global_type.hpp"
#include "ui.hpp"

namespace ui {
class UIManager {
public:
  UIManager(std::shared_ptr<renderer::Renderer> renderer,
            std::shared_ptr<logger::Logger> logger);

  global_type::ReturnStruct FeedCommand(const std::vector<std::string>& command);
private:

  global_type::ReturnStruct InitNextUI(UISession next_session);
  
  std::shared_ptr<renderer::Renderer> renderer_;
  std::shared_ptr<logger::Logger> logger_;

  std::shared_ptr<ui::UI> current_ui_;
};
  
} // namespace user_interface


#endif // UI_MANAGER_HPP