#include <algorithm>
#include <deque>
#include <iostream>
#include <map>

#include "common/matrix_2d.hpp"
#include "common/utils.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

enum class Type {
  kForwardMirror,
  kBackwardMirror,
  kEmpty,
  kHorizontalSplitter,
  kVerticalSplitter,
};

enum Direction { kUp = 1, kDown = 2, kLeft = 4, kRight = 8 };

using State = std::pair<Type, int>;
using Map = aoc::Matrix2D<State>;
using Coordinate = aoc::Vector2D<int>;

auto GetMap(std::ifstream& in) -> Map {
  auto [size_x, size_y] = aoc::size(in);

  auto map = Map(size_x, size_y, std::pair{Type::kEmpty, 0});
  auto line = std::string{};
  int y{0};
  while (std::getline(in, line)) {
    for (int x = 0; x < std::ssize(line); ++x) {
      if (line[x] == '/') {
        map.at(x, y) = {Type::kForwardMirror, 0};
      } else if (line[x] == '\\') {
        map.at(x, y) = {Type::kBackwardMirror, 0};
      } else if (line[x] == '-') {
        map.at(x, y) = {Type::kHorizontalSplitter, 0};
      } else if (line[x] == '|') {
        map.at(x, y) = {Type::kVerticalSplitter, 0};
      }
    }
    ++y;
  }
  return map;
}

}  // namespace

std::string Day16_1(std::ifstream& in) {
  auto map = GetMap(in);

  std::deque<std::pair<Coordinate, Direction>> to_process{};
  to_process.emplace_back(Coordinate{0, 0}, kLeft);
  const auto dir_map = std::map<Direction, Coordinate>{
      {kUp, {0, -1}}, {kDown, {0, 1}}, {kLeft, {-1, 0}}, {kRight, {1, 0}}};

  while (!to_process.empty()) {
    auto [coord, dir] = to_process.front();
    to_process.pop_front();

    if (!map.contains(coord.x, coord.y)) {
      continue;  // out of bounds
    }

    auto& map_val = map.at(coord.x, coord.y);
    map_val.second |= dir;

    // These are given from the perspektive of the receiving node, so the directions are flipped
    const auto propagate_laser = [&](Direction dir) {
      auto next = coord + dir_map.at(dir);
      if (!map.contains(next.x, next.y)) {
        return;  // out of bounds
      }

      auto next_val = map.at(next.x, next.y);
      switch (dir) {
        case Direction::kLeft:
          if ((next_val.second & kRight) != kRight) to_process.emplace_back(next, kRight);
          break;
        case Direction::kUp:
          if ((next_val.second & kDown) != kDown) to_process.emplace_back(next, kDown);
          break;
        case Direction::kRight:
          if ((next_val.second & kLeft) != kLeft) to_process.emplace_back(next, kLeft);
          break;
        case Direction::kDown:
          if ((next_val.second & kUp) != kUp) to_process.emplace_back(next, kUp);
          break;
      }
    };

    const auto propagate_map = std::map<Type, std::map<Direction, std::vector<Direction>>>{
        {Type::kForwardMirror,
         {{kLeft, {kUp}}, {kUp, {kLeft}}, {kRight, {kDown}}, {kDown, {kRight}}}},
        {Type::kBackwardMirror,
         {{kLeft, {kDown}}, {kUp, {kRight}}, {kRight, {kUp}}, {kDown, {kLeft}}}},
        {Type::kHorizontalSplitter,
         {{kLeft, {kRight}}, {kUp, {kLeft, kRight}}, {kRight, {kLeft}}, {kDown, {kLeft, kRight}}}},
        {Type::kVerticalSplitter,
         {{kLeft, {kUp, kDown}}, {kUp, {kDown}}, {kRight, {kUp, kDown}}, {kDown, {kUp}}}},
        {Type::kEmpty, {{kLeft, {kRight}}, {kUp, {kDown}}, {kRight, {kLeft}}, {kDown, {kUp}}}}};

    for (auto d : propagate_map.at(map_val.first).at(dir)) {
      propagate_laser(d);
    }
  }

  auto result = std::count_if(map.data().begin(), map.data().end(),
                              [](auto state) { return state.second != 0; });

  return std::to_string(result);
};

std::string Day16_2(std::ifstream& in) { return ""; };