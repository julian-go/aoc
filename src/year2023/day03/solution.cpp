#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

#include "common/matrix_2d.hpp"
#include "solutions.hpp"

using namespace std;

std::string Day03_1(std::ifstream& in) {
  string line;
  auto x_max = size_t{0}, y_max = size_t{0};
  while (std::getline(in, line)) {
    ++y_max;
  }
  x_max = line.size();
  in.clear();
  in.seekg(0);

  auto parts = vector<int>{};
  auto symbols = vector<pair<int, int>>{};
  auto map = Matrix2D<int>{x_max, y_max, -1};
  auto number = string{};
  auto x = int{0}, y = int{0};
  while (in >> line) {
    x = 0;
    for (char c : line) {
      if (isdigit(c)) {
        number.push_back(c);
        map.at(x, y) = parts.size();
      } else {
        if (!number.empty()) {
          parts.push_back(stoi(number));
          number.clear();
        }
        map.at(x, y) = -1;
        if (c != '.') {
          symbols.emplace_back(x, y);
        }
      }
      ++x;
    }
    ++y;
  }

  auto part_numbers = set<int>{};
  for (const auto& symbol : symbols) {
    for (int x = symbol.first - 1; x <= symbol.first + 1; ++x) {
      for (int y = symbol.second - 1; y <= symbol.second + 1; ++y) {
        auto val = map.contains(x, y) ? map.at(x, y) : -1;
        if (val >= 0) {
          part_numbers.emplace(val);
        }
      }
    }
  }

  auto result = int{0};
  for (auto const& pn : part_numbers) {
    result += parts[pn];
  }

  return to_string(result);
};

std::string Day03_2(std::ifstream& in) {
  string line;
  auto x_max = size_t{0}, y_max = size_t{0};
  while (std::getline(in, line)) {
    ++y_max;
  }
  x_max = line.size();
  in.clear();
  in.seekg(0);

  auto parts = vector<int>{};
  auto symbols = vector<pair<int, int>>{};
  auto map = Matrix2D<int>{x_max, y_max, -1};
  auto number = string{};
  auto x = int{0}, y = int{0};
  while (in >> line) {
    x = 0;
    for (char c : line) {
      if (isdigit(c)) {
        number.push_back(c);
        map.at(x, y) = parts.size();
      } else {
        if (!number.empty()) {
          parts.push_back(stoi(number));
          number.clear();
        }
        map.at(x, y) = -1;
        if (c == '*') {
          symbols.emplace_back(x, y);
        }
      }
      ++x;
    }
    ++y;
  }

  auto result = int{0};
  for (const auto& symbol : symbols) {
    auto ratios = set<int>{};
    for (int x = symbol.first - 1; x <= symbol.first + 1; ++x) {
      for (int y = symbol.second - 1; y <= symbol.second + 1; ++y) {
        auto val = map.contains(x, y) ? map.at(x, y) : -1;
        if (val >= 0) {
          ratios.emplace(parts[val]);
        }
      }
    }
    if (ssize(ratios) == 2) {
      result += accumulate(ratios.begin(), ratios.end(), 1, [](int a, int b) { return a * b; });
    }
  }

  return to_string(result);
};