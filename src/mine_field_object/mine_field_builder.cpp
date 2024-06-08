#include "mine_field_builder.hpp"

#include <iostream>
#include <memory>
#include "clock.hpp"

namespace mine_field {
std::shared_ptr<MineField> MineFieldBuilder::GetMineField() {
  return GetMineField(Difficulty::EASY);
}

std::shared_ptr<MineField> MineFieldBuilder::GetMineField(Difficulty dif) {
  switch (dif) {
  case Difficulty::EASY:
    return Generate(8, 10, 10);
    break;

  case Difficulty::MEDIUM:
    return Generate(14, 18, 40);
    break;

  case Difficulty::HARD:
    return Generate(20, 25, 80);
    break;

  case Difficulty::ULTRA_HARD:
    return Generate(25, 35, 110);
    break;

  default:
    return Generate(8, 10, 10);
    break;
  }
}

std::shared_ptr<MineField> MineFieldBuilder::GetMineField(uint16_t height, uint16_t width, uint16_t mines) {
  return Generate(height, width, mines);
}

static bool IsOutOfBound(Position pos, uint16_t height, uint16_t width) {
  if ((pos.row_ < 0) || (pos.row_ >= height)) { return true; }
  if ((pos.col_ < 0) || (pos.col_ >= width)) { return true; }
  return false;
}

std::shared_ptr<MineField> MineFieldBuilder::Generate(uint16_t height, uint16_t width, uint16_t mines) {
  mine_field_data map_data;
  // generate 2-dimensional vector
  for (uint16_t i = 0; i < height; i++) {
    std::vector<Cell> tmp_row{};
    for (uint16_t j = 0; j < width; j++) {
      tmp_row.push_back(Cell{.pos_={.row_=i,.col_=j}});
      std::cout << "generated 1 row with size: " << tmp_row.size() << std::endl;
    }
    map_data.push_back(tmp_row);
    std::cout << "added 1 row to local_mine_map_, current size: " << map_data.size() << std::endl;
  }

  // put mines into the map
  srand(Clock::GetUTC_ms());
  for (int generated_mine_count = 0; generated_mine_count < mines;) {
    uint16_t row = rand() % height;
    uint16_t col = rand() % width;
    if (IsOutOfBound(Position{.row_=row,.col_=col}, height, width)) {continue;}
    if (map_data[row][col].content_ == 9) {continue;}
    map_data[row][col].content_ = 9;
    generated_mine_count++;
  }

  // generate numbers base on around cells
  for (uint16_t i = 0; i < height; i++) {
    for (uint16_t j = 0; j < width; j++) {
      if (map_data[i][j].content_ != 9) {
        map_data[i][j].content_ = CountMinesAround(map_data[i][j].pos_, map_data);
      }
    }
  }
  
  return std::make_shared<MineField>(map_data);
}

uint16_t MineFieldBuilder::CountMinesAround(Position pos, mine_field_data& field) {
  uint16_t count = 0;
  // above cell
  if (pos.row_ > 0) { count += field[pos.row_ - 1][pos.col_].content_== 9 ? 1 : 0; }
  // left cell
  if (pos.col_ > 0) { count += field[pos.row_][pos.col_ - 1].content_== 9 ? 1 : 0; }
  // below cell
  if (pos.row_ < field.size() - 1) { count += field[pos.row_ + 1][pos.col_].content_== 9 ? 1 : 0; }
  // right cell
  if (pos.col_ < field[0].size() - 1) { count += field[pos.row_][pos.col_ + 1].content_== 9 ? 1 : 0; }

  // above left
  if ((pos.row_ > 0)&&(pos.col_ > 0)) { count += field[pos.row_ - 1][pos.col_ - 1].content_== 9 ? 1 : 0; }
  // above right
  if ((pos.row_ > 0)&&(pos.col_ < field[0].size() - 1)) { count += field[pos.row_ - 1][pos.col_ + 1].content_== 9 ? 1 : 0; }
  // below left
  if ((pos.row_ < field.size() - 1)&&(pos.col_ > 0)) { count += field[pos.row_ + 1][pos.col_ - 1].content_== 9 ? 1 : 0; }
  // below right
  if ((pos.row_ < field.size() - 1)&&(pos.col_ < field[0].size() - 1)) { count += field[pos.row_ + 1][pos.col_ + 1].content_== 9 ? 1 : 0; }

  return count;
}
} // namespace mine_field