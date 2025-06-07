#include "Input.hpp"

#include "IO/JSON.hpp"

#include <iostream>

#include <fstream>
#include <nlohmann/json.hpp>

namespace Ion {

std::unordered_map<Key, bool> Input::s_Current;
std::unordered_map<Key, bool> Input::s_Previous;
std::unordered_map<std::string, std::vector<Key>> Input::s_Bindings;

void Input::init() { loadBinding("keymaps.json"); }

void Input::onEvent(int key, bool isKeyDown) {
  Key mappedKey = static_cast<Key>(key);
  s_Current[mappedKey] = isKeyDown;

  // std::cout << "Key: " << key << std::endl;
}

void Input::update() { s_Previous = s_Current; }

bool Input::down(Key key) { return s_Current[key]; }

bool Input::pressed(Key key) { return s_Current[key] && !s_Previous[key]; }

bool Input::released(Key key) { return !s_Current[key] && s_Previous[key]; }

bool Input::action(const std::string &name) {
  auto it = s_Bindings.find(name);
  if (it == s_Bindings.end())
    return false;
  for (auto key : it->second) {
    if (down(key))
      return true;
  }
  return false;
}

bool Input::actionPressed(const std::string &name) {
  auto it = s_Bindings.find(name);
  if (it == s_Bindings.end())
    return false;
  for (auto key : it->second) {
    if (pressed(key))
      return true;
  }
  return false;
}

bool Input::actionReleased(const std::string &name) {
  auto it = s_Bindings.find(name);
  if (it == s_Bindings.end())
    return false;
  for (auto key : it->second) {
    if (released(key))
      return true;
  }
  return false;
}

const std::unordered_map<std::string, std::vector<Key>> &Input::getBindings() {
  return s_Bindings;
}

void Input::loadBinding(const std::string &path) {
  nlohmann::json data = Ion::IO::JSON::read(path);
  if (data.is_null())
    return;

  for (auto &[action, keys] : data.items()) {
    std::vector<Key> keyList;
    for (const auto &k : keys) {
      std::string keyStr = k.get<std::string>();

      // Harf tuşları için basit çeviri
      if (keyStr.length() == 1) {
        keyList.push_back(static_cast<Key>(toupper(keyStr[0])));
      }
      // Özel tuşlar
      else if (keyStr == "Enter")
        keyList.push_back(Key::Enter);
      else if (keyStr == "Escape")
        keyList.push_back(Key::Escape);
      else if (keyStr == "Space")
        keyList.push_back(Key::Space);
      else if (keyStr == "Left")
        keyList.push_back(Key::Left);
      else if (keyStr == "Right")
        keyList.push_back(Key::Right);
      else if (keyStr == "Up")
        keyList.push_back(Key::Up);
      else if (keyStr == "Down")
        keyList.push_back(Key::Down);
      else if (keyStr == "Left")
        keyList.push_back(Key::Left);
      else if (keyStr == "Backspace")
        keyList.push_back(Key::Backspace);
      else if (keyStr == "F1")
        keyList.push_back(Key::F1);
      // Gerekirse burada diğer tuşlar da manuel eklenebilir
    }
    s_Bindings[action] = keyList;
  }
}

} // namespace Ion
