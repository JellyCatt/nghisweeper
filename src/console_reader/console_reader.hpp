#ifndef CONSOLE_READER_HPP
#define CONSOLE_READER_HPP

#include <string>
#include <functional>

#include "command_reader.hpp"

namespace interact {
class ConsoleCommandReader : public CommandReader {
public:
  ConsoleCommandReader();
  global_type::ReturnStruct RegisterCommandHandler(CommandReaderCallbackType callback) override;
  global_type::ReturnStruct StartCommandReading() override;
  global_type::ReturnStruct StopCommandReading() override;
private:
  void ReaderLoop();
  void Terminate();
  bool is_running_;
  CommandReaderCallbackType command_callback_;
};
} // namespace console


#endif // CONSOLE_READER_HPP