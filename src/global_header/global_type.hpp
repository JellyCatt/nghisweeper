#ifndef GLOBAL_INCLUDE_HPP
#define GLOBAL_INCLUDE_HPP

#include <string>

namespace global_type {
enum class ReturnState {
  OK = 0,
  NOT_OK = 1,
  TERMINATED
};

struct ReturnStruct {
  ReturnState state_{ReturnState::NOT_OK};
  std::string info_{""};
};

} // namespace global_type

#endif // GLOBAL_INCLUDE_HPP