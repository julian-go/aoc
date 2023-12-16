#include <bitset>
#include <deque>
#include <iostream>

#include "common/matrix_2d.hpp"
#include "solutions.hpp"

namespace {

namespace part1 {
using Row = std::bitset<100>;
using Map = std::vector<Row>;
}  // namespace part1

namespace part2 {

enum class Type { kEmpty = 0, kSquare = 1, kRound = 2 };

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

void print(Matrix2D<Type> map) {
  for (size_t y = 0; y < map.sizeY(); ++y) {
    for (size_t x = 0; x < map.sizeX(); ++x) {
      switch (map.at(x, y)) {
        case Type::kRound:
          std::cout << 'O';
          break;
        case Type::kEmpty:
          std::cout << '.';
          break;
        case Type::kSquare:
          std::cout << '#';
          break;
      }
    }
    std::cout << std::endl;
  }
}

}  // namespace part2

}  // namespace

std::string Day14_1(std::ifstream& in) {
  using namespace part1;
  auto rounded = Map{};
  auto square = Map{};
  auto line = std::string{};

  while (std::getline(in, line)) {
    rounded.emplace_back();
    square.emplace_back();
    for (int i = 0; i < std::ssize(line); ++i) {
      if (line[i] == 'O') {
        rounded.back().set(i);
      } else if (line[i] == '#') {
        square.back().set(i);
      }
    }
  }

  bool settled = false;
  while (!settled) {
    settled = true;
    for (int i = 1; i < std::ssize(rounded); ++i) {
      auto occupied = rounded[i - 1] | square[i - 1];
      auto tmp = rounded[i - 1];
      rounded[i - 1] |= rounded[i] & ~occupied;
      if (tmp != rounded[i - 1]) {
        settled = false;
      }
      rounded[i] &= occupied;
      //      for (int j = 0; j < 10; ++j) {
      //        std::cout << (rounded[i - 1][j] ? 'O' : (square[i - 1][j] ? '#' : '.'));
      //      }
      //      std::cout << std::endl;
    }
    //    std::cout << std::endl;
  }

  const auto max_load = std::ssize(rounded);
  auto load = int{0};
  for (int i = 0; i < max_load; ++i) {
    load += (max_load - i) * rounded[i].count();
  }

  return std::to_string(load);
};

std::string Day14_2(std::ifstream& in) {
  using namespace part2;

  auto line = std::string{};
  auto map = Matrix2D<Type>{};

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

  //  for (int x = 0; x < map.sizeX(); ++x) {
  //    int put_idx{0};
  //    int num_put{0};
  //    for (int y = 0; y < map.sizeY(); ++y) {
  //      if (map.at(x, y) == Type::kRound) {
  //        ++num_put;
  //        map.at(x, y) = Type::kEmpty;
  //      } else if (map.at(x, y) == Type::kSquare) {
  //        for (int put_y = put_idx; put_y < put_idx + num_put; ++put_y) {
  //          map.at(x, put_y) = Type::kRound;
  //        }
  //        put_idx = y + 1;
  //        num_put = 0;
  //      }
  //    }
  //    for (int put_y = put_idx; put_y < put_idx + num_put; ++put_y) {
  //      map.at(x, put_y) = Type::kRound;
  //    }
  //  }
  //  print(map);

  int load{0};

  std::deque<int> pattern{0};
  int pattern_length = 0;
  int i;
  bool done = false;
  for (i = 0; i < 1000000000 && !done; ++i) {
    MoveNorth(map);
    MoveWest(map);
    MoveSouth(map);
    MoveEast(map);
    load = Load(map);
    constexpr auto kMinPatternLength = int{5};
    pattern.push_front(load);
    if (pattern.size() > 20) {
      pattern.pop_back();
    }
    for (int j = kMinPatternLength; j < 20; ++j) {
      bool pattern_found{true};
      for (int k = 0; k < j && pattern_found; ++k) {
        pattern_found = pattern[k] == pattern[k + j];
      }
      if (pattern_found) {
        done = true;
        pattern_length = j;
      } else if (done) {
        break;
      }
    }
    //    std::cout << load << std::endl;
  }

  auto result = pattern[pattern_length - ((1000000000 - (i - 1)) % pattern_length - 1)];
  return std::to_string(result);
};