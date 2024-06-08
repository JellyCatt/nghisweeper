#include "file_logger.hpp"
// #include "clock.hpp"

namespace logger {
FileLogger::FileLogger() {
  if (log_stream_.is_open()) {
    log_stream_.close();
  }
  log_stream_.open("mine_log.log", std::ios::out);
  Log("File logger started...");
}

FileLogger::~FileLogger() {
  Log("File logger is dying... :o");
  log_stream_.close();
}

void FileLogger::Log(const std::string& msg) {
  if (!log_stream_.is_open()) { return; }
  log_stream_ << msg << std::endl;
  log_stream_.flush();
}

void FileLogger::LogDebug(const std::string& msg) {}
void FileLogger::LogInfo(const std::string& msg) {}
void FileLogger::LogWarning(const std::string& msg) {}
void FileLogger::LogError(const std::string& msg) {}
void FileLogger::LogIncident(const std::string& msg) {}
} // namespace logger
