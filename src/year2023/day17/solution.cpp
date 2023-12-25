#include <array>
#include <complex>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "common/matrix_2d.hpp"
#include "common/matrix_nd.hpp"
#include "common/utils.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

constexpr int kNumheadings{4};

using Map = aoc::Matrix2D<int>;
using Cache = aoc::Matrix<int, 3>;
using Heading = aoc::Vector2D;
using Coordinate = aoc::Vector2D;
using namespace std::complex_literals;

struct State {
  Coordinate coord;
  Heading heading;
};

using Path = aoc::Matrix<State, 3>;

int index(Heading heading) {
  if (heading == Heading(1, 0))
    return 0;
  else if (heading == Heading(0, -1))
    return 1;
  else if (heading == Heading(-1, 0))
    return 2;
  else if (heading == Heading(0, 1))
    return 3;
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

void DebugPrint(const Coordinate& goal, const Heading& final_heading, const Path& previous,
                const Map& map) {
  auto path = std::unordered_map<Coordinate, char, Coordinate::Hash>{};
  path[goal] = 'o';
  auto current = State{goal, final_heading};
  while (current.coord != Coordinate{0, 0}) {
    auto prev = previous.at(current.coord.x, current.coord.y, index(current.heading));
    if (current.heading == Heading{-1, 0}) {
      path[current.coord] = '<';
    } else if (current.heading == Heading{1, 0}) {
      path[current.coord] = '>';
    } else if (current.heading == Heading{0, -1}) {
      path[current.coord] = '^';
    } else if (current.heading == Heading{0, 1}) {
      path[current.coord] = 'v';
    }
    current = prev;
  }

  for (int y{0}; y < map.sizeY(); ++y) {
    for (int x{0}; x < map.sizeX(); ++x) {
      if (path.contains(Coordinate{x, y})) {
        std::cout << path[Coordinate{x, y}];
      } else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
}

template <int kMinStraight, int kMaxStraight>
auto Solve(std::ifstream& in) -> int {
  constexpr bool kDebug{false};

  auto map = GetMap(in);
  auto heading = Heading{1, 0};
  auto goal = Coordinate(map.sizeX() - 1, map.sizeY() - 1);
  auto distance = Cache(map.sizeX(), map.sizeY(), kNumheadings);
  auto previous = Path(map.sizeX(), map.sizeY(), kNumheadings);
  distance.fill(std::numeric_limits<int>::max());
  distance.at(0, 0, index(heading)) = 0;

  auto GetDistance = [&distance](const State& state) -> int& {
    return distance.at(state.coord.x, state.coord.y, index(state.heading));
  };

  auto GetPrevious = [&previous](const State& state) -> State& {
    return previous.at(state.coord.x, state.coord.y, index(state.heading));
  };

  auto predicate = [&goal, &GetDistance](const State& lhs, const State& rhs) {
    return ((goal - lhs.coord).manhattan() + GetDistance(lhs)) >
           ((goal - rhs.coord).manhattan() + GetDistance(rhs));
  };

  auto q = std::priority_queue<State, std::deque<State>, decltype(predicate)>(predicate);
  q.push(State{{0, 0}, heading});
  int result{std::numeric_limits<int>::max()};
  auto final_heading = Heading{0, 0};
  while (!q.empty()) {
    auto state = q.top();
    q.pop();

    if (state.coord == goal) {
      auto d = distance.at(state.coord.x, state.coord.y, index(state.heading));
      if (d < result) {
        result = d;
        final_heading = state.heading;
      }
      continue;
    }

    auto delta_cost = 0;
    for (int i = 1; i <= kMaxStraight; ++i) {
      auto pivot = state;
      pivot.coord += state.heading * i;

      if (!map.contains(pivot.coord)) break;

      delta_cost += map.at(pivot.coord);

      if (i < kMinStraight) continue;

      const auto go_left = State{pivot.coord, pivot.heading.Left()};
      const auto go_right = State{pivot.coord, pivot.heading.Right()};
      const auto next_states = std::array<State, 2>{go_left, go_right};

      for (const auto& s : next_states) {
        auto d = GetDistance(state) + delta_cost;
        if (d < GetDistance(s)) {
          GetDistance(s) = d;
          GetPrevious(s) = state;
          q.push(s);
        }
      }
    }
  }

  if constexpr (kDebug) DebugPrint(goal, final_heading, previous, map);

  return result;
}

}  // namespace

std::string Day17_1(std::ifstream& in) { return std::to_string(Solve<1, 3>(in)); };

std::string Day17_2(std::ifstream& in) { return std::to_string(Solve<4, 10>(in)); };