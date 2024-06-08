#ifndef COMMAND_READER_HPP
#define COMMAND_READER_HPP

#include <memory>
#include "global_type.hpp"
#include "logger.hpp"

namespace interact {
class CommandReader {
public:
  using CommandReaderCallbackType=std::function<global_type::ReturnStruct(const std::string&)>;
  virtual global_type::ReturnStruct RegisterCommandHandler(CommandReaderCallbackType callback) = 0;
  virtual global_type::ReturnStruct StartCommandReading() = 0;
  virtual global_type::ReturnStruct StopCommandReading() = 0;

  void SetLogger(std::shared_ptr<logger::Logger> logger) { logger_ = logger; }

protected:
  std::shared_ptr<logger::Logger> logger_;
};
} // namespace interact

#endif // COMMAND_READER_HPP