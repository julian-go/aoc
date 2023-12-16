#include <bitset>
#include <deque>
#include <iostream>

#include "common/matrix_2d.hpp"
#include "common/utils.hpp"
#include "solutions.hpp"

namespace {

using aoc::Matrix2D;

enum class Type { kEmpty = 0, kSquare = 1, kRound = 2 };
using Map = Matrix2D<Type>;

auto GetMap(std::ifstream& in) -> Map {
  Map map;
  auto line = std::string{};
  int y{0};
  while (std::getline(in, line)) {
    if (map.sizeX() == 0) {
      map.resize(line.size(), line.size());
      map.fill(Type::kEmpty);
    }

    for (int x = 0; x < std::ssize(line); ++x) {
      if (line[x] == 'O') {
        map.at(x, y) = Type::kRound;
      } else if (line[x] == '#') {
        map.at(x, y) = Type::kSquare;
      }
    }

    ++y;
  }
  return map;
}

void MoveNorth(Matrix2D<Type>& map) {
  for (int x = 0; x < map.sizeX(); ++x) {
    int put_idx{0};
    int num_put{0};
    for (int y = 0; y < map.sizeY(); ++y) {
      if (map.at(x, y) == Type::kRound) {
        ++num_put;
        map.at(x, y) = Type::kEmpty;
      } else if (map.at(x, y) == Type::kSquare) {
        for (int put_y = put_idx; put_y < put_idx + num_put; ++put_y) {
          map.at(x, put_y) = Type::kRound;
        }
        put_idx = y + 1;
        num_put = 0;
      }
    }
    for (int put_y = put_idx; put_y < put_idx + num_put; ++put_y) {
      map.at(x, put_y) = Type::kRound;
    }
  }
}

void MoveSouth(Matrix2D<Type>& map) {
  for (int x = 0; x < map.sizeX(); ++x) {
    int put_idx{static_cast<int>(map.sizeY()) - 1};
    int num_put{0};
    for (int y = map.sizeY() - 1; y >= 0; --y) {
      if (map.at(x, y) == Type::kRound) {
        ++num_put;
        map.at(x, y) = Type::kEmpty;
      } else if (map.at(x, y) == Type::kSquare) {
        for (int put_y = put_idx; put_y > put_idx - num_put; --put_y) {
          map.at(x, put_y) = Type::kRound;
        }
        put_idx = y - 1;
        num_put = 0;
      }
    }
    for (int put_y = put_idx; put_y > put_idx - num_put; --put_y) {
      map.at(x, put_y) = Type::kRound;
    }
  }
}

void MoveWest(Matrix2D<Type>& map) {
  for (int y = 0; y < map.sizeY(); ++y) {
    int put_idx{0};
    int num_put{0};
    for (int x = 0; x < map.sizeX(); ++x) {
      if (map.at(x, y) == Type::kRound) {
        ++num_put;
        map.at(x, y) = Type::kEmpty;
      } else if (map.at(x, y) == Type::kSquare) {
        for (int put_x = put_idx; put_x < put_idx + num_put; ++put_x) {
          map.at(put_x, y) = Type::kRound;
        }
        put_idx = x + 1;
        num_put = 0;
      }
    }
    for (int put_x = put_idx; put_x < put_idx + num_put; ++put_x) {
      map.at(put_x, y) = Type::kRound;
    }
  }
}

void MoveEast(Matrix2D<Type>& map) {
  for (int y = 0; y < map.sizeY(); ++y) {
    int put_idx{static_cast<int>(map.sizeX()) - 1};
    int num_put{0};
    for (int x = map.sizeX() - 1; x >= 0; --x) {
      if (map.at(x, y) == Type::kRound) {
        ++num_put;
        map.at(x, y) = Type::kEmpty;
      } else if (map.at(x, y) == Type::kSquare) {
        for (int put_x = put_idx; put_x > put_idx - num_put; --put_x) {
          map.at(put_x, y) = Type::kRound;
        }
        put_idx = x - 1;
        num_put = 0;
      }
    }
    for (int put_x = put_idx; put_x > put_idx - num_put; --put_x) {
      map.at(put_x, y) = Type::kRound;
    }
  }
}

int Load(Matrix2D<Type> map) {
  const int max_load = map.sizeY();
  auto load = int{0};
  for (int y = 0; y < max_load; ++y) {
    for (int x = 0; x < map.sizeX(); ++x) {
      if (map.at(x, y) == Type::kRound) load += (max_load - y);
    }
  }
  return load;
}

}  // namespace

std::string Day14_1(std::ifstream& in) {
  auto map = GetMap(in);
  MoveNorth(map);
  return std::to_string(Load(map));
};

std::string Day14_2(std::ifstream& in) {
  auto map = GetMap(in);

  std::deque<int> pattern{};
  int pattern_length = 0;
  int cycle{0};
  while (cycle <= 1'000'000'000) {
    cycle++;

    MoveNorth(map);
    MoveWest(map);
    MoveSouth(map);
    MoveEast(map);

    pattern.push_front(Load(map));
    if (pattern.size() > 20) {
      pattern.pop_back();
    }

    pattern_length = aoc::find_pattern_size(pattern.begin(), pattern.end(), 5);
    if (pattern_length > 0) {
      break;
    }
  }

  const int cycles_passed{cycle};  // not zero indexed
  constexpr int max_cycles{1'000'000'000};
  const int cycles_to_go{max_cycles - cycles_passed};
  const int pattern_remainder{cycles_to_go % pattern_length};
  const int result{pattern[pattern_length - pattern_remainder]};
  return std::to_string(result);
};