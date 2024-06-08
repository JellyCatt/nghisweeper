#ifndef MINE_FIELD_OBJ_HPP
#define MINE_FIELD_OBJ_HPP

#include <string>
#include <vector>
#include <memory>
#include "logger.hpp"
namespace mine_field {

enum class UserInterract {
  FLAGGED,
  QUESTIONED,
  NO
};

struct Position {
  uint16_t row_{0};
  uint16_t col_{0};
};

struct Cell
{
  Position pos_;
  bool is_revealed_{false};
  UserInterract user_interract_{UserInterract::NO};
  uint8_t content_{0};
};

using mine_field_data=std::vector<std::vector<Cell>>;
class MineField {
  enum class ReturnCode {
    SUCCESS,
    FAILED,
    GAME_END,
    UNKNOWN
  };
  struct ReturnStruct {
    ReturnCode code_{ReturnCode::UNKNOWN};
    std::string info_{""};
  };
  
public:
  MineField(mine_field_data data);

  // run-time interraction
  ReturnStruct Flag(Position pos);
  ReturnStruct Question(Position pos);
  ReturnStruct Reveal(Position pos);
  ReturnStruct SmartReveal(Position pos);

  std::vector<std::vector<Cell>> GetMapData() const { return map_data_; }
  uint16_t GetHeight() const { return height_; }
  uint16_t GetWidth() const { return width_; }

  void SetLogger(std::shared_ptr<logger::Logger> logger) { logger_ = logger; }

private:
  // internal method
  bool IsOutOfBound(Position pos);
  // original info
  std::vector<std::vector<Cell>> map_data_;
  uint16_t height_;
  uint16_t width_;
  uint16_t mines_count_;

  std::shared_ptr<logger::Logger> logger_;
};
} // namespace mine_field
#endif // MINE_FIELD_OBJ_HPP