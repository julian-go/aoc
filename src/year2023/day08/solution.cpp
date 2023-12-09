#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>

#include "solutions.hpp"

using Coordinate = std::array<char, 3>;

struct CoordinateHash {
  std::size_t operator()(const Coordinate& c) const {
    return static_cast<std::size_t>(c[0]) | (static_cast<std::size_t>(c[1]) << 8) |
           (static_cast<std::size_t>(c[2]) << 16);
  }
};

using Map = std::unordered_map<Coordinate, std::pair<Coordinate, Coordinate>, CoordinateHash>;

auto GetInstructions(std::ifstream& in) -> std::vector<bool> {
  auto line = std::string{};
  std::getline(in, line);
  auto instructions = std::vector<bool>{};
  for (const auto& c : line) {
    instructions.emplace_back(c == 'L');
  }
  return instructions;
}

auto GetMapAndGhosts(std::ifstream& in) -> std::tuple<Map, std::vector<Coordinate>> {
  Map map{};
  auto ghosts = std::vector<Coordinate>{};
  auto line = std::string{};
  while (std::getline(in, line)) {
    auto ss = std::stringstream{line};
    Coordinate from{}, to_left{}, to_right{};
    ss >> from[0] >> from[1] >> from[2];
    ss.ignore(4);
    ss >> to_left[0] >> to_left[1] >> to_left[2];
    ss.ignore(2);
    ss >> to_right[0] >> to_right[1] >> to_right[2];
    map[from] = {to_left, to_right};
    if (from[2] == 'A') {
      ghosts.emplace_back(from);
    }
  }
  return {map, ghosts};
}

auto GetMap(std::ifstream& in) -> Map {
  auto [map, ghosts] = GetMapAndGhosts(in);
  return map;
}

std::string Day08_1(std::ifstream& in) {
  auto instructions = GetInstructions(in);
  in.ignore();
  auto map = GetMap(in);

  auto current = Coordinate{'A', 'A', 'A'};
  auto goal = Coordinate{'Z', 'Z', 'Z'};
  int steps{0};
  int current_instruction{0};
  while (current != goal) {
    current = instructions[current_instruction] ? map[current].first : map[current].second;
    ++steps;
    ++current_instruction;
    current_instruction %= instructions.size();
  }
  return std::to_string(steps);
};

std::string Day08_2(std::ifstream& in) {
  auto instructions = GetInstructions(in);
  in.ignore();
  auto [map, ghosts] = GetMapAndGhosts(in);
  auto predicate = [](const Coordinate& c) { return c[2] == 'Z'; };
  auto ghost_steps = std::vector<std::int64_t>{};

  // The ghosts always follow the same loop, therefore we can just find the least common multiple
  for (auto& ghost : ghosts) {
    int current_instruction{0};
    int steps{0};
    while (ghost[2] != 'Z') {
      ghost = instructions[current_instruction] ? map[ghost].first : map[ghost].second;
      ++steps;
      ++current_instruction;
      current_instruction %= instructions.size();
    }
    ghost_steps.emplace_back(steps);
  }

  auto result = ghost_steps.front();
  for (const auto& step : ghost_steps) {
    result = std::lcm(result, step);
  }
  return std::to_string(result);
};