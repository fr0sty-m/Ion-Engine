#pragma once

#include "Key.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace Ion {

class Input {
public:
  static void init();
  static void update();
  static void loadBinding(const std::string &path);

  static bool down(Key key);
  static bool pressed(Key key);
  static bool released(Key key);

  static bool action(const std::string &name);
  static bool actionPressed(const std::string &name);
  static bool actionReleased(const std::string &name);

  static const std::unordered_map<std::string, std::vector<Key>> &getBindings();

  static void onEvent(int key, bool isKeyDown);

private:
  static std::unordered_map<Key, bool> s_Current;
  static std::unordered_map<Key, bool> s_Previous;

  static std::unordered_map<std::string, std::vector<Key>> s_Bindings;
};

} // namespace Ion
