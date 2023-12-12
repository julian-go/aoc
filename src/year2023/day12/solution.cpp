#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

#include "solutions.hpp"
namespace {

struct Record {
  std::string data;
  std::vector<bool> unknown;
  std::vector<int> groups;

  bool valid() const {
    int count{0};
    auto u = unknown.begin();
    auto g = groups.begin();
    for (auto c : data) {
      const auto damaged = (c == '#') || (c == '?' && *u);
      if (damaged) {
        count++;
      } else {
        if (g != groups.end() && count == *g) {
          g++;
        }
        count = 0;
      }

      if (c == '?') {
        u++;
      }
    }

    if (g != groups.end() && count == *g) {
      g++;
    }

    return g == groups.end();
  }

  void clear() {
    data.clear();
    unknown.clear();
    groups.clear();
  }
};

}  // namespace

std::string Day12_1(std::ifstream& in) {
  auto line = std::string{};
  auto result = int{0};
  auto r = Record{};
  r.clear();
  while (getline(in, r.data, ' ')) {
    getline(in, line);
    auto ss = std::stringstream{line};
    int value{0};
    while (ss >> value) {
      r.groups.push_back(value);
      ss.ignore(1);
    }

    int expected_damaged = std::accumulate(r.groups.begin(), r.groups.end(), 0);
    int confirmed_damaged = std::count(r.data.begin(), r.data.end(), '#');
    r.unknown.resize(std::count(r.data.begin(), r.data.end(), '?'), false);
    std::fill(r.unknown.rbegin(), r.unknown.rbegin() + (expected_damaged - confirmed_damaged),
              true);

    do {
      if (r.valid()) {
        ++result;
      }
    } while (std::next_permutation(r.unknown.begin(), r.unknown.end()));

    r.clear();
  }

  return std::to_string(result);
};

std::string Day12_2(std::ifstream& in) { return ""; };