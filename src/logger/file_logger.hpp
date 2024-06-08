#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "logger.hpp"
#include <string>
#include <fstream>

namespace logger {
class FileLogger : public Logger {
public:
  FileLogger();
  ~FileLogger();
  void LogDebug(const std::string& msg) override;
  void LogInfo(const std::string& msg) override;
  void LogWarning(const std::string& msg) override;
  void LogError(const std::string& msg) override;
  void LogIncident(const std::string& msg) override;
  void Log(const std::string& msg) override;
private:
  std::ofstream log_stream_;
};
} // namespace logger

#endif // FILE_LOGGER_HPP