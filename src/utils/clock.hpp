#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class Clock {
public:
  static int64_t GetUTC_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
  }
};

#endif // CLOCK_HPP