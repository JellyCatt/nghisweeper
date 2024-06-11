#include "mine_field_object.hpp"

#include <iostream>

#include "clock.hpp"
#include "log_macro.hpp"

namespace mine_field
{
MineField::MineField(mine_field_data data) : map_data_(data),
                                             height_(data.size() - 1),
                                             width_(data[0].size() - 1) {
}

bool MineField::IsOutOfBound(Position pos) {
  LOG("MineField::IsOutOfBound() called" << pos.row_ << " " << pos.col_);
  if ((pos.row_ < 0) || (pos.row_ >= height_)) { return true; }
  if ((pos.col_ < 0) || (pos.col_ >= width_)) { return true; }
  return false;
}

global_type::ReturnStruct MineField::Flag(Position pos) {
  LOG("MineField::Flag() called at " << pos.row_ << " " << pos.col_);
  if (IsOutOfBound(pos)) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Out of bound!!!"};
  }
  if (map_data_[pos.row_][pos.col_].is_revealed_) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Flag FAILED!! Cell already reveiled..."};
  }
  if (map_data_[pos.row_][pos.col_].user_interract_ == UserInterract::FLAGGED) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Flag FAILED!! Cell already flagged..."};
  }

  LOG("MineField::Flag() FLAG successfully" << pos.row_ << " " << pos.col_);
  map_data_[pos.row_][pos.col_].user_interract_ = UserInterract::FLAGGED;
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK,.info_=""};
}

global_type::ReturnStruct MineField::Question(Position pos) {
  if (IsOutOfBound(pos)) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Out of bound!!!"};
  }
  if (map_data_[pos.row_][pos.col_].is_revealed_) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Flag FAILED!! Cell already reveiled..."};
  }
  if (map_data_[pos.row_][pos.col_].user_interract_ == UserInterract::QUESTIONED) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Flag FAILED!! Cell already flagged..."};
  }

  LOG("MineField::Question() QUESTION successfully" << pos.row_ << " " << pos.col_);
  map_data_[pos.row_][pos.col_].user_interract_ = UserInterract::QUESTIONED;
  return global_type::ReturnStruct{.state_=global_type::ReturnState::OK,.info_=""};
}

global_type::ReturnStruct MineField::Reveal(Position pos) {
  if (IsOutOfBound(pos)) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Out of bound!!!"};
  }
  if (map_data_[pos.row_][pos.col_].is_revealed_) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Flag FAILED!! Cell already reveiled..."};
  }

  LOG("MineField::Reveal() REVEALING " << pos.row_ << " " << pos.col_);
  if (map_data_[pos.row_][pos.col_].content_ < 9) {
    map_data_[pos.row_][pos.col_].is_revealed_ = true;
    return global_type::ReturnStruct{.state_=global_type::ReturnState::OK,.info_=""};
  } else {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="You stepped on a bomb :)"};
  }
}

global_type::ReturnStruct MineField::SmartReveal(Position pos) {
  if (IsOutOfBound(pos)) {
    return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Out of bound!!!"};
  }
  return global_type::ReturnStruct{.state_=global_type::ReturnState::NOT_OK,.info_="Feature not yet supported :)"};
}

} // namespace mine_field
