#include "JSON.hpp"

namespace Ion::IO {

nlohmann::json JSON::read(const std::string &path) {
  std::string content = File::readText(path);
  if (content.empty())
    return {};

  return content;
}

} // namespace Ion::IO
