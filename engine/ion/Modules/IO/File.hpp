#pragma once

#include <string>
#include <vector>

namespace Ion::IO {

class File {
public:
  static std::string readText(const std::string &path);
  static bool writeText(const std::string &path, const std::string &content);

  static std::vector<char> readBinary(const std::string &path);
  static bool writeBinary(const std::string &path,
                          const std::vector<char> &data);

  static bool exists(const std::string &path);
};

} // namespace Ion::IO
