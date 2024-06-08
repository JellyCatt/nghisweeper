#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

namespace logger {
class Logger {
public:
  enum class Level { kDebug = 1, kInfo, kWarning, kError, kIncident };

  Level GetLevel() { return level_; }
  void SetLevel(Level level) { level_ = level; }
  virtual void LogDebug(const std::string& msg) = 0;
  virtual void LogInfo(const std::string& msg) = 0;
  virtual void LogWarning(const std::string& msg) = 0;
  virtual void LogError(const std::string& msg) = 0;
  virtual void LogIncident(const std::string& msg) = 0;
  virtual void Log(const std::string& msg) = 0;

private:
  Level level_;
};
} // namespace logger


#endif // LOGGER_HPP