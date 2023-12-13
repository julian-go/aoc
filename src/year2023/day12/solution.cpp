#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>

#include "solutions.hpp"

namespace {

using int_t = std::int64_t;

struct Problem {
  std::string data{};
  std::vector<int> groups{};
  int max_set{0};
};

class Cache {
 public:
  bool contains(int i, int n_set, int n_group, int current_group) {
    return data.contains(hash(i, n_set, n_group, current_group));
  }

  void insert(int i, int n_set, int n_group, int current_group, int_t value) {
    data[hash(i, n_set, n_group, current_group)] = value;
  }

  int_t& at(int i, int n_set, int n_group, int current_group) {
    return data[hash(i, n_set, n_group, current_group)];
  }

 private:
  inline int64_t hash(int i, int n_set, int n_group, int current_group) {
    return static_cast<std::int8_t>(i) | (static_cast<std::int8_t>(n_set) << 8) |
           (static_cast<std::int8_t>(n_group) << 16) |
           (static_cast<std::int8_t>(current_group) << 24);
  }
  std::map<std::int64_t, int_t> data;
};

// DP Cost function
auto g(const Problem& p, Cache& c, int i = 0, int n_set = 0, int n_group = 0, int current_group = 0)
    -> int_t {
  // i - current index in the string
  // n_set - amount of bits already set in this branch
  // n_group - length of currently counted group
  // current_group - group that is currently being worked on

  // Memoization
  if (c.contains(i, n_set, n_group, current_group)) {
    return c.at(i, n_set, n_group, current_group);
  }

  int_t result = 0;

  if (i == std::ssize(p.data)) {
    if (current_group >= p.groups.size()) {
      return 1;
    } else {
      return 0;
    }
  }

  if (n_group != 0 && n_group > p.groups[current_group]) {
    return 0;  // the current group is too long
  }

  if (p.data[i] == '#') {
    result += g(p, c, i + 1, n_set, n_group + 1, current_group);
  } else if (p.data[i] == '.') {
    if (n_group == p.groups[current_group]) {
      result += g(p, c, i + 1, n_set, 0, current_group + 1);
    } else if (n_group == 0) {
      result += g(p, c, i + 1, n_set, 0, current_group);
    } else {
      return 0;  // the current group was too short
    }
  } else if (p.data[i] == '?') {
    if (n_set < p.max_set) {
      result += g(p, c, i + 1, n_set + 1, n_group + 1, current_group);
    }
    // case where we place a '.'
    if (n_group == p.groups[current_group]) {
      result += g(p, c, i + 1, n_set, 0, current_group + 1);
    } else if (n_group == 0) {
      result += g(p, c, i + 1, n_set, 0, current_group);
    }
  }

  c.insert(i, n_set, n_group, current_group, result);
  return result;
}

template <int factor>
auto solve(std::ifstream& in) -> int_t {
  auto line = std::string{};
  int_t result{0};
  while (getline(in, line)) {
    auto ss = std::stringstream{line};
    auto p = Problem{};
    getline(ss, p.data, ' ');
    int value{0};
    while (ss >> value) {
      p.groups.push_back(value);
      ss.ignore(1);
    }

    {
      // Repetition for part 2
      auto groups = p.groups;
      auto data = p.data;
      for (int i = 0; i < factor - 1; ++i) {
        p.data += "?" + data;
        std::copy(groups.begin(), groups.end(), std::back_inserter(p.groups));
      }
    }

    // For easier processing
    p.data += '.';

    int expected_damaged = std::accumulate(p.groups.begin(), p.groups.end(), 0);
    int confirmed_damaged = std::count(p.data.begin(), p.data.end(), '#');
    p.max_set = expected_damaged - confirmed_damaged;

    auto c = Cache{};
    auto x = g(p, c);
    result += x;
  }
  return result;
}

}  // namespace

std::string Day12_1(std::ifstream& in) { return std::to_string(solve<1>(in)); };

std::string Day12_2(std::ifstream& in) { return std::to_string(solve<5>(in)); };