#include "mine_field_object.hpp"

#include <iostream>

#include "clock.hpp"

namespace mine_field
{
MineField::MineField(mine_field_data data) : map_data_(data),
                                             height_(data.size() - 1),
                                             width_(data[0].size() - 1) {
}

bool MineField::IsOutOfBound(Position pos) {
  if ((pos.row_ < 0) || (pos.row_ >= height_)) { return true; }
  if ((pos.col_ < 0) || (pos.col_ >= width_)) { return true; }
  return false;
}

MineField::ReturnStruct MineField::Flag(Position pos) {
  if (IsOutOfBound(pos)) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Out of bound!!!"};
  }
  if (map_data_[pos.row_][pos.col_].is_revealed_) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Flag FAILED!! Cell already reveiled..."};
  }
  if (map_data_[pos.row_][pos.col_].user_interract_ == UserInterract::FLAGGED) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Flag FAILED!! Cell already flagged..."};
  }
  map_data_[pos.row_][pos.col_].user_interract_ = UserInterract::FLAGGED;
  return ReturnStruct{.code_=ReturnCode::SUCCESS,.info_=""};
}

MineField::ReturnStruct MineField::Question(Position pos) {
  if (IsOutOfBound(pos)) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Out of bound!!!"};
  }
  if (map_data_[pos.row_][pos.col_].is_revealed_) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Flag FAILED!! Cell already reveiled..."};
  }
  if (map_data_[pos.row_][pos.col_].user_interract_ == UserInterract::QUESTIONED) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Flag FAILED!! Cell already flagged..."};
  }
  map_data_[pos.row_][pos.col_].user_interract_ = UserInterract::QUESTIONED;
  return ReturnStruct{.code_=ReturnCode::SUCCESS,.info_=""};
}

MineField::ReturnStruct MineField::Reveal(Position pos) {
  if (IsOutOfBound(pos)) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Out of bound!!!"};
  }
  if (map_data_[pos.row_][pos.col_].is_revealed_) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Flag FAILED!! Cell already reveiled..."};
  }
  if (map_data_[pos.row_][pos.col_].content_ < 9) {
    map_data_[pos.row_][pos.col_].is_revealed_ = true;
    return ReturnStruct{.code_=ReturnCode::SUCCESS,.info_=""};
  } else {
    return ReturnStruct{.code_=ReturnCode::GAME_END,.info_="You stepped on a bomb :)"};
  }
}

MineField::ReturnStruct MineField::SmartReveal(Position pos) {
  if (IsOutOfBound(pos)) {
    return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Out of bound!!!"};
  }
  return ReturnStruct{.code_=ReturnCode::FAILED,.info_="Feature not yet supported :)"};
}

} // namespace mine_field
