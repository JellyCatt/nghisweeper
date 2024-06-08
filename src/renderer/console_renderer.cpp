#include "console_renderer.hpp"
#include "log_macro.hpp"

namespace renderer {

void ConsoleRenderer::PrintOneDashRow(uint16_t map_width) {
  auto width = map_width;
  for (int col = 0; col < (width * 2 + 1); col++) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

void ConsoleRenderer::Render(RenderRequest request) {
  LOG("ConsoleRenderer::Render render called");
  ClearScreen();
  if (request.GetMineField() != nullptr) {
    PrintMap(request.GetMineField()->GetMapData());
  }
  PrintAdditionalInfo(request.GetAdditionalInfo());
}

uint8_t ConsoleRenderer::GetRenderChar(mine_field::Cell cell_info) {
  if (!cell_info.is_revealed_) {
    if (cell_info.user_interract_ == mine_field::UserInterract::FLAGGED) {
      return CHAR_FLAG;
    }
    if (cell_info.user_interract_ == mine_field::UserInterract::QUESTIONED) {
      return CHAR_QUES;
    } else {
      return CHAR_NONE;
    }
  } else {
    if (cell_info.content_ >= 9) {
      return CHAR_BOMB;
    } else {
      return (cell_info.content_ + 48);
    }
  }
}

void ConsoleRenderer::ClearScreen() { std::cout << "\033[2J\033[1;1H"; }

void ConsoleRenderer::PrintMap(mine_field::mine_field_data map_data) {
  auto height = map_data.size();
  auto width = map_data[0].size();

  PrintOneDashRow(width);
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      uint8_t print_char = GetRenderChar(map_data[row][col]);
      std::cout << "|" << print_char;
    }
    std::cout << "|" << std::endl;
    PrintOneDashRow(width);
  }
}

void ConsoleRenderer::PrintAdditionalInfo(RenderRequest::AdditionalInfoType add_info) {
  std::cout << "-------------------" << std::endl;

  // printing hint_and_help
  auto hint_help_it = add_info.find("hint_and_help");
  if (hint_help_it == add_info.end()) {
    std::cout << "There are no hints or helps in this session..." << std::endl;
  } else {
    for (auto& it : add_info["hint_and_help"]) {
      std::cout << it.second << std::endl;
    }
  }

  // printing user's interact options
  auto user_options = add_info.find("user_options");
  if (user_options == add_info.end()) {
    std::cout << "There are no user's options in this session..." << std::endl;
  } else {
    for (auto& it : add_info["user_options"]) {
      std::cout << it.first << ": " << it.second << std::endl;
    }
  }
  std::cout << std::endl;
}
}