#include <array>
#include <iostream>
#include <list>
#include <sstream>

#include "solutions.hpp"

namespace {

auto hash(std::string_view s) -> int {
  int hash = 0;
  for (auto c : s) {
    hash += static_cast<int>(c);
    hash *= 17;
    hash %= 256;
  }
  return hash;
}

}  // namespace

std::string Day15_1(std::ifstream& in) {
  auto line = std::string{};
  int result{0};
  while (std::getline(in, line, ',')) {
    result += hash(line);
  }
  return std::to_string(result);
};

std::string Day15_2(std::ifstream& in) {
  auto line = std::string{};
  auto hash_map = std::array<std::list<std::pair<std::string, int>>, 256>{};
  while (std::getline(in, line, ',')) {
    auto label = std::string{};
    int value{0};
    auto ss = std::stringstream{line};
    char c;
    while (ss >> c, c != '=' && c != '-') {
      label.push_back(c);
    }
    ss >> value;

    auto h = hash(label);
    auto& box = hash_map[h];
    const auto find_label = [&label](const auto& p) { return p.first == label; };
    if (c == '-') {
      box.remove_if(find_label);
    } else if (c == '=') {
      auto it = std::find_if(box.begin(), box.end(), find_label);
      if (it != box.end()) {
        it->second = value;
      } else {
        box.emplace_back(label, value);
      }
    }
  }

  int result{0};
  int i{1};
  for (const auto& box : hash_map) {
    int j = 1;
    for (const auto& lens : box) {
      result += i * j * lens.second;
      ++j;
    }
    ++i;
  }
  return std::to_string(result);
};
