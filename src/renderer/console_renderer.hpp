#ifndef CONSOLE_RENDERER_HPP
#define CONSOLE_RENDERER_HPP

#include "renderer.hpp"

namespace renderer {
#define CHAR_NONE " "
#define CHAR_BOMB "@"
#define CHAR_FLAG "F"
#define CHAR_QUES "?"
#define CHAR_SAFE "0"

#define START_UNDERLINE "\033[4m"
#define END_UNDERLINE "\033[0m"


class ConsoleRenderer : public Renderer {
public:
  ConsoleRenderer() = default;
  void Render(RenderRequest request) override;
private:
  void PrintMap(mine_field::mine_field_data map_data);
  void PrintAdditionalInfo(RenderRequest::AdditionalInfoType add_info);

  void ClearScreen();
  void PrintOneDashRow(uint16_t map_width);
  std::string GetRenderChar(mine_field::Cell cell_info);
};
}

#endif