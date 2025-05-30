#pragma once

#include "File.hpp"

#include <nlohmann/json.hpp>

namespace Ion::IO {

class JSON {
public:
  static nlohmann::json read(const std::string &path);
  static bool write(const std::string &path, const nlohmann::json &data);
};

} // namespace Ion::IO
