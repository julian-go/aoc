#include <array>
#include <complex>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>

#include "common/matrix_2d.hpp"
#include "common/utils.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

constexpr int kMaxMapSize{150};
constexpr int kMaxStraight{10};
constexpr int kNumheadings{4};
constexpr int kCacheSize{kMaxMapSize * kMaxMapSize * kNumheadings * kMaxStraight};

using Map = aoc::Matrix2D<int>;
template <typename T>
using Cache = std::vector<T>;
using Heading = std::complex<double>;
using Coordinate = aoc::Vector2D;
using namespace std::complex_literals;

struct State {
  Coordinate coord;
  Heading heading;
  int steps;
};

auto Index(int x, int y, int steps, Heading heading) -> int {
  if (heading == 1.0) {
    return x + y * kMaxMapSize + steps * kMaxMapSize * kMaxMapSize +
           0 * kMaxMapSize * kMaxMapSize * kMaxStraight;
  } else if (heading == -1.0) {
    return x + y * kMaxMapSize + steps * kMaxMapSize * kMaxMapSize +
           1 * kMaxMapSize * kMaxMapSize * kMaxStraight;
  } else if (heading == 1.0i) {
    return x + y * kMaxMapSize + steps * kMaxMapSize * kMaxMapSize +
           2 * kMaxMapSize * kMaxMapSize * kMaxStraight;
  } else if (heading == -1.0i) {
    return x + y * kMaxMapSize + steps * kMaxMapSize * kMaxMapSize +
           3 * kMaxMapSize * kMaxMapSize * kMaxStraight;
  }
}

template <typename T>
auto Set(Cache<T>& c, int x, int y, int steps, Heading heading, T value) {
  c[Index(x, y, steps, heading)] = value;
}

template <typename T>
auto Get(Cache<T>& c, int x, int y, int steps, Heading heading) -> T {
  return c[Index(x, y, steps, heading)];
}

template <typename T>
auto Set(Cache<T>& c, const State& s, T value) {
  c[Index(s.coord.x, s.coord.y, s.steps, s.heading)] = value;
}

template <typename T>
auto Get(Cache<T>& c, const State& s) -> T {
  return c[Index(s.coord.x, s.coord.y, s.steps, s.heading)];
}

auto GetMap(std::ifstream& in) -> Map {
  auto [size_x, size_y] = aoc::size(in);
  auto map = Map(size_x, size_y);
  for (int y{0}; y < size_y; ++y) {
    for (int x{0}; x < size_x; ++x) {
      char c{};
      in >> c;
      map.at(x, y) = c - '0';
    }
  }
  return map;
}

}  // namespace

std::string Day17_1(std::ifstream& in) {
  // auto map = GetMap(in);

  // auto distance = Cache<int>{};
  // distance.resize(kCacheSize, std::numeric_limits<int>::max());
  // Set(distance, 0, 0, 0, 1.0, 0);
  // auto visited = Cache<bool>{};
  // visited.resize(kCacheSize, false);

  // auto goal = Coordinate(map.sizeX() - 1, map.sizeY() - 1);
  // auto predicate = [&goal, &distance](const State& lhs, const State& rhs) {
  //   // Nodes closer to the goal have higher priority
  //   return ((goal - lhs.coord).manhattan() + Get(distance, lhs)) >
  //          ((goal - rhs.coord).manhattan() + Get(distance, rhs));
  // };

  // auto q = std::priority_queue<State, std::deque<State>, decltype(predicate)>(predicate);
  // q.push(State{{0, 0}, 1.0, 0});
  // while (!q.empty()) {
  //   auto state = q.top();
  //   q.pop();

  //  if (state.coord == goal) {
  //    /* for (int step = 0; step < kMaxStraight; ++step) {
  //       for (int y = 0; y < 13; ++y) {
  //         for (int x = 0; x < 13; ++x) {
  //           auto cost = Get(distance, x, y, step, 1);
  //           if (cost < 10000) {
  //             std::cout << std::setfill(' ') << std::setw(3) << (cost < 10000 ? cost : cost) << '
  //     '; } else { std::cout << "... ";
  //           }
  //         }
  //         std::cout << std::endl;
  //       }
  //       std::cout << std::endl;
  //     }
  //     std::cout << "-----------------" << std::endl;
  //     std::cout << std::endl;*/
  //    return std::to_string(Get(distance, state));
  //  }

  //  if (Get(visited, state)) {
  //    continue;
  //  }

  //  Set(visited, state, true);

  //  if (state.steps < kMaxStraight - 1) {
  //    // can go straight
  //    auto next_state = state;
  //    next_state.steps++;
  //    if (std::real(state.heading) != 0) {
  //      next_state.coord += Coordinate(std::real(state.heading), 0);
  //    } else {
  //      next_state.coord += Coordinate(0, -std::imag(state.heading));
  //    }
  //    if (map.contains(next_state.coord.x, next_state.coord.y) && !Get(visited, next_state)) {
  //      auto dist = Get(distance, state);
  //      dist += map.at(next_state.coord.x, next_state.coord.y);
  //      if (dist < Get(distance, next_state)) {
  //        Set(distance, next_state, dist);
  //        q.push(next_state);
  //      }
  //    }
  //  }

  //  {
  //    // Turn right
  //    auto next_state = state;
  //    next_state.heading *= -1.0i;
  //    next_state.steps = 0;
  //    if (std::real(next_state.heading) != 0) {
  //      next_state.coord += Coordinate(std::real(next_state.heading), 0);
  //    } else {
  //      next_state.coord += Coordinate(0, -std::imag(next_state.heading));
  //    }
  //    if (map.contains(next_state.coord.x, next_state.coord.y) && !Get(visited, next_state)) {
  //      auto dist = Get(distance, state);
  //      dist += map.at(next_state.coord.x, next_state.coord.y);
  //      if (dist < Get(distance, next_state)) {
  //        Set(distance, next_state, dist);
  //        q.push(next_state);
  //      }
  //    }
  //  }

  //  {
  //    // Turn left
  //    auto next_state = state;
  //    next_state.heading *= 1.0i;
  //    next_state.steps = 0;
  //    if (std::real(next_state.heading) != 0) {
  //      next_state.coord += Coordinate(std::real(next_state.heading), 0);
  //    } else {
  //      next_state.coord += Coordinate(0, -std::imag(next_state.heading));
  //    }
  //    if (map.contains(next_state.coord.x, next_state.coord.y) && !Get(visited, next_state)) {
  //      auto dist = Get(distance, state) + map.at(next_state.coord.x, next_state.coord.y);
  //      if (dist < Get(distance, next_state)) {
  //        Set(distance, next_state, dist);
  //        q.push(next_state);
  //      }
  //    }
  //  }
  //}

  return std::to_string(0);
};

std::string Day17_2(std::ifstream& in) {
  return std::to_string(0);
  auto map = GetMap(in);

  auto previous = std::map<aoc::Vector2D, aoc::Vector2D>{};
  auto distance = Cache<int>{};
  distance.resize(kCacheSize, std::numeric_limits<int>::max());
  Set(distance, 0, 0, 0, 1.0, 0);
  auto visited = Cache<bool>{};
  visited.resize(kCacheSize, false);

  auto goal = Coordinate(map.sizeX() - 1, map.sizeY() - 1);
  auto predicate = [&goal, &distance](const State& lhs, const State& rhs) {
    // Nodes closer to the goal have higher priority
    return (0 * (goal - lhs.coord).manhattan() + Get(distance, lhs)) >
           (0 * (goal - rhs.coord).manhattan() + Get(distance, rhs));
  };

  auto q = std::priority_queue<State, std::deque<State>, decltype(predicate)>(predicate);
  q.push(State{{0, 0}, 1.0, 0});
  int result{std::numeric_limits<int>::max()};
  while (!q.empty()) {
    auto state = q.top();
    q.pop();

    if (state.coord == goal) {
      if (state.steps >= 3) {
        result = std::min(result, Get(distance, state));
      }
      continue;
    }

    // if (Get(visited, state)) {
    //   continue;
    // }

    // Set(visited, state, true);

    if (state.steps < kMaxStraight - 1) {
      // can go straight
      auto next_state = state;
      next_state.steps++;
      if (std::real(state.heading) != 0) {
        next_state.coord += Coordinate(std::real(state.heading), 0);
      } else {
        next_state.coord += Coordinate(0, -std::imag(state.heading));
      }
      if (map.contains(next_state.coord.x, next_state.coord.y) && !Get(visited, next_state)) {
        auto dist = Get(distance, state);
        dist += map.at(next_state.coord.x, next_state.coord.y);
        if (dist < Get(distance, next_state)) {
          if (next_state.coord == goal) {
            // std::cout << next_state.steps << ": " << dist << std::endl;
          }
          Set(distance, next_state, dist);
          previous[next_state.coord] = state.coord;
          q.push(next_state);
        }
      }
    }

    if (state.steps >= 3) {
      // Turn right
      auto next_state = state;
      next_state.heading *= -1.0i;
      next_state.steps = 0;
      if (std::real(next_state.heading) != 0) {
        next_state.coord += Coordinate(std::real(next_state.heading), 0);
      } else {
        next_state.coord += Coordinate(0, -std::imag(next_state.heading));
      }
      if (map.contains(next_state.coord.x, next_state.coord.y) && !Get(visited, next_state)) {
        auto dist = Get(distance, state);
        dist += map.at(next_state.coord.x, next_state.coord.y);
        if (dist < Get(distance, next_state)) {
          Set(distance, next_state, dist);
          previous[next_state.coord] = state.coord;
          q.push(next_state);
        }
      }
    }

    if (state.steps >= 3) {
      // Turn left
      auto next_state = state;
      next_state.heading *= 1.0i;
      next_state.steps = 0;
      if (std::real(next_state.heading) != 0) {
        next_state.coord += Coordinate(std::real(next_state.heading), 0);
      } else {
        next_state.coord += Coordinate(0, -std::imag(next_state.heading));
      }
      if (map.contains(next_state.coord.x, next_state.coord.y) && !Get(visited, next_state)) {
        auto dist = Get(distance, state) + map.at(next_state.coord.x, next_state.coord.y);
        if (dist < Get(distance, next_state)) {
          Set(distance, next_state, dist);
          previous[next_state.coord] = state.coord;
          q.push(next_state);
        }
      }
    }
  }

  return std::to_string(result);
};