#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>

#include "solutions.hpp"

using namespace std;

std::string Day04_1(std::ifstream& in) {
  string line;
  auto result = int{0};
  while (getline(in, line)) {
    set<int> winning{}, owned{};
    auto ss = stringstream{line};
    ss.ignore(20, ':');
    int number;
    while (ss >> number) {
      winning.emplace(number);
    }
    ss.clear();
    ss.ignore(1);
    while (ss >> number) {
      owned.emplace(number);
    }

    vector<int> intersection;
    set_intersection(winning.begin(), winning.end(), owned.begin(), owned.end(),
                     std::back_inserter(intersection));
    if (ssize(intersection) > 0) {
      result += 1 << (ssize(intersection) - 1);
    }
  }
  return to_string(result);
};

std::string Day04_2(std::ifstream& in) {
  auto line = string{};
  auto values = vector<int>{};
  auto result = int{0};
  while (getline(in, line)) {
    set<int> winning{}, owned{};
    auto ss = stringstream{line};
    ss.ignore(20, ':');
    int number;
    while (ss >> number) {
      winning.emplace(number);
    }
    ss.clear();
    ss.ignore(1);
    while (ss >> number) {
      owned.emplace(number);
    }

    auto intersection = vector<int>{};
    set_intersection(winning.begin(), winning.end(), owned.begin(), owned.end(),
                     std::back_inserter(intersection));
    values.emplace_back(ssize(intersection));
  }

  for (auto it = values.rbegin(); it != values.rend(); ++it) {
    int tmp{1};
    for (int i = 1; i <= *it; ++i) {
      tmp += *(it - i);
    }
    *it = tmp;
  }
  return to_string(accumulate(values.begin(), values.end(), 0));
};