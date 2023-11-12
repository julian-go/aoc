#include <iostream>
#include <limits>
#include <vector>
#include <numeric>

#include "solutions.hpp"

std::string Day01_1(std::ifstream& in) {
  std::vector<int> input;
  int num;
  while (in >> num) {
    input.push_back(num);
  }

  auto previous = std::numeric_limits<int>::max();
  auto count = int{0};
  for (const auto& i : input) {
    if (i > previous) {
      ++count;
    }
    previous = i;
  }
  return std::to_string(count);
};

std::string Day01_2(std::ifstream& in) {
  std::vector<int> input;
  int num;
  while (in >> num) {
    input.push_back(num);
  }

  constexpr auto window_size = int{3};
  auto count = int{0};
  for (auto it = input.begin(); it + window_size != input.end(); ++it) {
    auto sum_1 = std::accumulate(it, it + window_size, 0);
    auto sum_2 = std::accumulate(it + 1, it + window_size + 1, 0);
    if (sum_2 > sum_1) {
	  ++count;
	}
  }
  return std::to_string(count);
};