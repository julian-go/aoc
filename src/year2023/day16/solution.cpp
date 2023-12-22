#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <unordered_map>

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
using Coordinate = aoc::Vector2D;

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

auto Solve(Map map, std::pair<Coordinate, Direction> start) -> int {
  std::deque<std::pair<Coordinate, Direction>> to_process{start};

  int result{0};
  while (!to_process.empty()) {
    auto [coord, dir] = to_process.front();
    to_process.pop_front();

    auto& map_val = map.at(coord.x, coord.y);
    if (map_val.second == 0) result++;
    map_val.second |= dir;

    // These are given from the perspektive of the receiving node, so the directions are flipped
    const auto propagate_laser = [&](Direction dir) {
      aoc::Vector2D next;
      switch (dir) {
        case kUp:
          next = coord + aoc::Vector2D(0, -1);
          break;
        case kDown:
          next = coord + aoc::Vector2D(0, 1);
          break;
        case kLeft:
          next = coord + aoc::Vector2D(-1, 0);
          break;
        case kRight:
          next = coord + aoc::Vector2D(1, 0);
          break;
      }
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

    switch (map_val.first) {
      case Type::kForwardMirror:
        switch (dir) {
          case Direction::kLeft:
            propagate_laser(Direction::kUp);
            break;
          case Direction::kUp:
            propagate_laser(Direction::kLeft);
            break;
          case Direction::kRight:
            propagate_laser(Direction::kDown);
            break;
          case Direction::kDown:
            propagate_laser(Direction::kRight);
            break;
        }
        break;

      case Type::kBackwardMirror:
        switch (dir) {
          case Direction::kLeft:
            propagate_laser(Direction::kDown);
            break;
          case Direction::kUp:
            propagate_laser(Direction::kRight);
            break;
          case Direction::kRight:
            propagate_laser(Direction::kUp);
            break;
          case Direction::kDown:
            propagate_laser(Direction::kLeft);
            break;
        }
        break;

      case Type::kHorizontalSplitter:
        switch (dir) {
          case Direction::kLeft:
            propagate_laser(Direction::kRight);
            break;
          case Direction::kUp:
            propagate_laser(Direction::kLeft);
            propagate_laser(Direction::kRight);
            break;
          case Direction::kRight:
            propagate_laser(Direction::kLeft);
            break;
          case Direction::kDown:
            propagate_laser(Direction::kLeft);
            propagate_laser(Direction::kRight);
            break;
        }
        break;

      case Type::kVerticalSplitter:
        switch (dir) {
          case Direction::kLeft:
            propagate_laser(Direction::kUp);
            propagate_laser(Direction::kDown);
            break;
          case Direction::kUp:
            propagate_laser(Direction::kDown);
            break;
          case Direction::kRight:
            propagate_laser(Direction::kUp);
            propagate_laser(Direction::kDown);
            break;
          case Direction::kDown:
            propagate_laser(Direction::kUp);
            break;
        }
        break;

      case Type::kEmpty:
        switch (dir) {
          case Direction::kLeft:
            propagate_laser(Direction::kRight);
            break;
          case Direction::kUp:
            propagate_laser(Direction::kDown);
            break;
          case Direction::kRight:
            propagate_laser(Direction::kLeft);
            break;
          case Direction::kDown:
            propagate_laser(Direction::kUp);
        }
    }
  }

  return result;
}

}  // namespace

std::string Day16_1(std::ifstream& in) {
  auto map = GetMap(in);
  auto result = Solve(map, {{0, 0}, kLeft});
  return std::to_string(result);
};

std::string Day16_2(std::ifstream& in) {
  auto map = GetMap(in);
  auto result{0};
  int size = map.sizeX();
  for (int i = 0; i < size; ++i) {
    result = std::max(result, Solve(map, {{i, 0}, kUp}));
    result = std::max(result, Solve(map, {{i, size - 1}, kDown}));
    result = std::max(result, Solve(map, {{0, i}, kLeft}));
    result = std::max(result, Solve(map, {{size - 1, i}, kRight}));
  }
  return std::to_string(result);
};