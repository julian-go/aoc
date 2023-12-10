#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "common/matrix_2d.hpp"
#include "solutions.hpp"

enum Direction { kUp = 1, kRight = 2, kDown = 4, kLeft = 8 };

auto GetMap(std::ifstream& in) -> std::tuple<Matrix2D<int>, std::pair<int, int>> {
  std::string line;
  auto x_max = size_t{0}, y_max = size_t{0};
  while (std::getline(in, line)) {
    ++y_max;
  }
  x_max = line.size();
  in.clear();
  in.seekg(0);

  const auto kMap = std::unordered_map<char, int>{{'|', kUp | kDown},
                                                  {'-', kLeft | kRight},
                                                  {'L', kRight | kUp},
                                                  {'J', kLeft | kUp},
                                                  {'7', kLeft | kDown},
                                                  {'F', kRight | kDown},
                                                  {'.', 0},
                                                  {'S', 0}};
  auto start = std::pair{0, 0};
  auto map = Matrix2D<int>{x_max, y_max, 0};
  for (int y = 0; y < y_max; ++y) {
    std::getline(in, line);
    for (int x = 0; x < x_max; ++x) {
      map.at(x, y) = kMap.at(line[x]);
      if (line[x] == 'S') {
        start.first = x;
        start.second = y;
      }
    }
  }

  int sx = start.first, sy = start.second;
  if (map.contains(sx, sy - 1) && map.at(sx, sy - 1) & kDown) {
    map.at(sx, sy) |= kUp;
  }
  if (map.contains(sx, sy + 1) && map.at(sx, sy + 1) & kUp) {
    map.at(sx, sy) |= kDown;
  }
  if (map.contains(sx - 1, sy) && map.at(sx - 1, sy) & kRight) {
    map.at(sx, sy) |= kLeft;
  }
  if (map.contains(sx + 1, sy) && map.at(sx + 1, sy) & kLeft) {
    map.at(sx, sy) |= kRight;
  }

  return {map, start};
}

auto FillMap(Matrix2D<int> map, std::pair<int, int> start) -> Matrix2D<int> {
  auto distances = Matrix2D<int>{map.sizeX(), map.sizeY(), -1};
  distances.at(start.first, start.second) = 0;
  auto queue = std::queue<std::pair<int, int>>{};
  queue.push(start);
  while (!queue.empty()) {
    auto [x, y] = queue.front();
    queue.pop();

    auto local_distance = distances.at(x, y);
    auto condition = [&](auto x, auto y) {
      return map.contains(x, y) &&
             (distances.at(x, y) == -1 || (distances.at(x, y) >= local_distance + 1));
    };
    if ((map.at(x, y) & kUp) && condition(x, y - 1)) {
      queue.push({x, y - 1});
      distances.at(x, y - 1) = local_distance + 1;
    }
    if ((map.at(x, y) & kRight) && condition(x + 1, y)) {
      queue.push({x + 1, y});
      distances.at(x + 1, y) = local_distance + 1;
    }
    if ((map.at(x, y) & kDown) && condition(x, y + 1)) {
      queue.push({x, y + 1});
      distances.at(x, y + 1) = local_distance + 1;
    }
    if ((map.at(x, y) & kLeft) && condition(x - 1, y)) {
      queue.push({x - 1, y});
      distances.at(x - 1, y) = local_distance + 1;
    }
  }
  return distances;
}

auto TestPointInsideLoop(const Matrix2D<int>& map, const Matrix2D<int>& distances, int x, int y)
    -> bool {
  if (distances.at(x, y) != -1) {
    return false;
  }

  // If we pass an uneven amount of "up" elements, we are inside the main loop
  int up_count{0};
  for (int i = x; i < distances.sizeX(); ++i) {
    if (distances.at(i, y) != -1 && map.at(i, y) & kUp) {
      ++up_count;
    }
  }

  return (up_count % 2) != 0;
}

std::string Day10_1(std::ifstream& in) {
  auto [map, start] = GetMap(in);
  auto distances = FillMap(map, start);
  int result = *std::max_element(distances.data().begin(), distances.data().end());
  return std::to_string(result);
};

std::string Day10_2(std::ifstream& in) {
  auto [map, start] = GetMap(in);
  auto distances = FillMap(map, start);
  int result{0};
  for (int y = 0; y < distances.sizeY(); ++y) {
    for (int x = 0; x < distances.sizeX(); ++x) {
      if (TestPointInsideLoop(map, distances, x, y)) {
        result++;
      }
    }
  }
  return std::to_string(result);
};