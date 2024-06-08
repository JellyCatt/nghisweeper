#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "mine_field_object.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>

#include "logger.hpp"

namespace renderer {
/*RenderRequest's additional_info structure:
"hint_and_help" : ____
"user_options": */
class RenderRequest {
public:
  using AdditionalInfoType=std::map<std::string, std::map<std::string, std::string>>;
  RenderRequest(std::shared_ptr<mine_field::MineField> mine_field,
                AdditionalInfoType additional_info) :
                mine_field_(mine_field), additional_info_(additional_info) {}

  std::shared_ptr<mine_field::MineField> GetMineField() const { return mine_field_; }
  AdditionalInfoType GetAdditionalInfo() const { return additional_info_; }
private:
  std::shared_ptr<mine_field::MineField> mine_field_;
  std::map<std::string,std::map<std::string,std::string>> additional_info_;
};
class Renderer {
public:
  virtual void Render(RenderRequest request) = 0;

  void SetLogger(std::shared_ptr<logger::Logger> logger) { logger_ = logger; }

protected:
  std::shared_ptr<logger::Logger> logger_;
};
} // namespace renderer
#endif // RENDERER_HPP