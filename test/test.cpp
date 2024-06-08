#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <sstream>

class Clock {
public:
  static int64_t GetUTC_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
  }
};

class Base {
public:
  virtual void DoSomething() = 0;
private:
};

int main() {

  return 0;
}