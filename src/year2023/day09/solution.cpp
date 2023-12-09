#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>

#include "solutions.hpp"

auto GetSequence(std::string line) -> std::vector<int> {
  auto ss = std::stringstream{line};
  auto sequence = std::vector<int>{};
  auto value = int{};
  while (ss >> value) {
    sequence.push_back(value);
  }
  return sequence;
}

auto Derivative(std::vector<int> sequence) -> std::vector<int> {
  auto derivative = std::vector<int>{};
  derivative.reserve(sequence.size() - 1);
  for (auto it = sequence.begin(); it + 1 != sequence.end(); ++it) {
    derivative.push_back(*(it + 1) - *it);
  }
  return derivative;
}

auto Extrapolate(std::vector<int> sequence) -> int {
  auto derivatives = std::vector<std::vector<int>>{};
  derivatives.push_back(Derivative(sequence));
  while (!std::all_of(derivatives.back().begin(), derivatives.back().end(),
                      [](auto x) { return x == 0; })) {
    derivatives.push_back(Derivative(derivatives.back()));
  }
  auto last_derivative = 0;
  for (auto it = derivatives.rbegin(); it != derivatives.rend(); ++it) {
    last_derivative += it->back();
  }
  return sequence.back() + last_derivative;
}

auto BackExtrapolate(std::vector<int> sequence) -> int {
  auto derivatives = std::vector<std::vector<int>>{};
  derivatives.push_back(Derivative(sequence));
  while (!std::all_of(derivatives.back().begin(), derivatives.back().end(),
                      [](auto x) { return x == 0; })) {
    derivatives.push_back(Derivative(derivatives.back()));
  }
  auto last_derivative = 0;
  for (auto it = derivatives.rbegin(); it != derivatives.rend(); ++it) {
    last_derivative = it->front() - last_derivative;
  }
  return sequence.front() - last_derivative;
}

std::string Day09_1(std::ifstream& in) {
  auto line = std::string{};
  auto result = int64_t{0};
  while (std::getline(in, line)) {
    auto sequence = GetSequence(line);
    result += Extrapolate(sequence);
  }

  return std::to_string(result);
};

std::string Day09_2(std::ifstream& in) {
  auto line = std::string{};
  auto result = int64_t{0};
  while (std::getline(in, line)) {
    auto sequence = GetSequence(line);
    result += BackExtrapolate(sequence);
  }

  return std::to_string(result);
};