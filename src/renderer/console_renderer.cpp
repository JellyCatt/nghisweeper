#include "console_renderer.hpp"

#include <unistd.h> 
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

std::string ConsoleRenderer::GetRenderChar(mine_field::Cell cell_info) {
  if (!cell_info.is_revealed_) {
    if (cell_info.user_interract_ == mine_field::UserInterract::FLAGGED) {
      return std::string(CHAR_FLAG);
    }
    if (cell_info.user_interract_ == mine_field::UserInterract::QUESTIONED) {
      return std::string(CHAR_QUES);
    } else {
      return std::string(CHAR_NONE);
    }
  } else {
    if (cell_info.content_ >= 9) {
      return std::string(CHAR_BOMB);
    } else {
      return std::to_string(cell_info.content_);
    }
  }
}

void ConsoleRenderer::ClearScreen() { system("clear"); }

void ConsoleRenderer::PrintMap(mine_field::mine_field_data map_data) {
  auto height = map_data.size();
  auto width = map_data[0].size();

  PrintOneDashRow(width);
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      std::string print_char = GetRenderChar(map_data[row][col]);
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