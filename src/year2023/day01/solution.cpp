#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

#include "solutions.hpp"

using namespace std;

std::string Day01_1(ifstream& in) {
  string line;
  auto result = int{0};
  constexpr auto predicate = [](auto c) { return isdigit(c); };
  while (in >> line) {
    auto first = *ranges::find_if(line, predicate);
    auto last = *ranges::find_if(line | views::reverse, predicate);
    result += 10 * (first - '0') + (last - '0');
  }
  return std::to_string(result);
};

std::string Day01_2(std::ifstream& in) {
  std::string line;
  auto result = int{0};
  const auto numbers_s =
      array{pair{"zero", "0"},  pair{"one", "1"},  pair{"two", "2"}, pair{"three", "3"},
            pair{"four", "4"},  pair{"five", "5"}, pair{"six", "6"}, pair{"seven", "7"},
            pair{"eight", "8"}, pair{"nine", "9"}};
  constexpr auto predicate = [](auto c) { return isdigit(c); };
  while (in >> line) {
    auto modified_line = line;
    // Build a new string, replacing the digit names with the digits themselves
    for (const auto& number : numbers_s) {
      auto index = line.find(number.first);
      if (index != string::npos) {
        modified_line.replace(index, 1, number.second);
      }
      index = line.rfind(number.first);
      if (index != string::npos) {
        modified_line.replace(index, 1, number.second);
      }
    }
    // Apply first solution
    auto first = *ranges::find_if(modified_line, predicate);
    auto last = *ranges::find_if(modified_line | views::reverse, predicate);
    result += 10 * (first - '0') + (last - '0');
  }
  return std::to_string(result);
};