#include "File.hpp"

#include <filesystem>
#include <fstream>

namespace Ion::IO {

std::string File::readText(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    return "";

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  return content;
}

bool File::writeText(const std::string &path, const std::string &content) {
  std::ofstream file(path);
  if (!file.is_open())
    return false;

  file << content;
  return true;
}

std::vector<char> File::readBinary(const std::string &path) {
  std::ifstream file(path, std::ios::binary);
  if (!file.is_open())
    return {};

  return std::vector<char>((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
}

bool File::writeBinary(const std::string &path, const std::vector<char> &data) {
  std::ofstream file(path, std::ios::binary);
  if (!file.is_open())
    return false;

  file.write(data.data(), data.size());
  return true;
}

bool File::exists(const std::string &path) {
  return std::filesystem::exists(path);
}

} // namespace Ion::IO
