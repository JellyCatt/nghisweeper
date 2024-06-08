#ifndef LOG_MACRO_HPP
#define LOG_MACRO_HPP

#include <sstream>

#define LOG(msg)                  \
  {                               \
    if (logger_ != nullptr) {     \
      std::ostringstream os;      \
      os << msg;                  \
      logger_->Log(os.str());     \
    }                             \
  }

#endif // LOG_MACRO_HPP