#include "JSON.hpp"

namespace Ion::IO {

nlohmann::json JSON::read(const std::string &path) {
  std::string content = File::readText(path);
  if (content.empty())
    return {};
}

} // namespace Ion::IO
