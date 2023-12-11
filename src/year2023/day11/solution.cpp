#include <bitset>
#include <cstdint>
#include <numeric>
#include <vector>

#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

constexpr auto kMaxMapSize = int{200};
using Occupancy = std::array<bool, kMaxMapSize>;
using Coordinate = aoc::Vector2D<int>;

auto ParseInput(std::ifstream& in) -> std::tuple<std::vector<Coordinate>, Occupancy, Occupancy> {
  auto galaxies = std::vector<Coordinate>{};
  Occupancy row_occupancy{}, column_occupancy{};
  row_occupancy.fill(true);
  column_occupancy.fill(true);
  auto line = std::string{};
  int y{0};
  while (getline(in, line)) {
    int x{0};
    for (auto c : line) {
      if (c == '#') {
        row_occupancy[y] = false;
        column_occupancy[x] = false;
        galaxies.emplace_back(x, y);
      }
      x++;
    }
    y++;
  }
  return {galaxies, row_occupancy, column_occupancy};
}

template <std::int64_t expansion>
auto ComputeDistances(std::vector<Coordinate> galaxies, Occupancy row, Occupancy col)
    -> std::int64_t {
  std::int64_t result{0};
  constexpr auto k = expansion - 1;
  for (int i = 0; i < galaxies.size(); ++i) {
    for (int j = i + 1; j < galaxies.size(); ++j) {
      auto distance = (galaxies[i] - galaxies[j]).length();
      auto from = aoc::Vector2D{std::min(galaxies[i].x, galaxies[j].x),
                                std::min(galaxies[i].y, galaxies[j].y)};
      auto to = aoc::Vector2D{std::max(galaxies[i].x, galaxies[j].x),
                              std::max(galaxies[i].y, galaxies[j].y)};
      distance += k * std::accumulate(row.begin() + from.y, row.begin() + to.y, 0LL);
      distance += k * std::accumulate(col.begin() + from.x, col.begin() + to.x, 0LL);
      result += distance;
    }
  }
  return result;
}

}  // namespace

std::string Day11_1(std::ifstream& in) {
  auto [galaxies, row_occupancy, col_occupancy] = ParseInput(in);
  auto result = ComputeDistances<2>(galaxies, row_occupancy, col_occupancy);
  return std::to_string(result);
};

std::string Day11_2(std::ifstream& in) {
  auto [galaxies, row_occupancy, col_occupancy] = ParseInput(in);
  auto result = ComputeDistances<1'000'000>(galaxies, row_occupancy, col_occupancy);
  return std::to_string(result);
};