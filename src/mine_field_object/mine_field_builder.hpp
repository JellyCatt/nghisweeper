#ifndef MINE_FIELD_BUILDER_HPP
#define MINE_FIELD_BUILDER_HPP

#include <vector>
#include <string>
#include <memory>

#include "mine_field_object.hpp"
#include "logger.hpp"

namespace mine_field {
enum class Difficulty {
  EASY,
  MEDIUM,
  HARD,
  ULTRA_HARD,
  CUSTOM
};
class MineFieldBuilder {
public:
  MineFieldBuilder() = default;

  std::shared_ptr<MineField> GetMineField();
  std::shared_ptr<MineField> GetMineField(Difficulty dif);
  std::shared_ptr<MineField> GetMineField(uint16_t height, uint16_t width, uint16_t mines);

  void SetLogger(std::shared_ptr<logger::Logger> logger) { logger_ = logger; }

private:
  std::shared_ptr<MineField> Generate(uint16_t height, uint16_t width, uint16_t mines);
  uint16_t CountMinesAround(Position pos, mine_field_data& field);

  std::shared_ptr<logger::Logger> logger_;
};
}

#endif // MINE_FIELD_BUILDER_HPP