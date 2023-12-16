#include <bitset>
#include <iostream>
#include <optional>
#include <vector>

#include "solutions.hpp"

namespace {

using Map = std::vector<std::int32_t>;

bool check_bit(std::uint32_t bits) { return bits && !(bits & (bits - 1)); }

std::optional<int> FindSymmetry(Map map, int tolerance = 0) {
  for (auto a = map.begin(), b = map.begin() + 1; b != map.end(); ++a, ++b) {
    auto c = std::make_reverse_iterator(a);
    auto d = b;
    c--;
    auto tol = tolerance;
    while (true) {
      bool exactly_one_error = check_bit(*c ^ *d);
      if (exactly_one_error && tol > 0) {
        tol--;
      } else if (*c != *d) {
        break;  // too many bit errors
      }
      ++c;
      ++d;
      if (c == map.rend() || d == map.end()) {
        if (tol > 0) {
          break;  // not enough bit errors
        }
        return std::distance(map.begin(), a) + 1;
      }
    }
  }
  return std::nullopt;
}

auto GetMap(std::ifstream& in, std::vector<std::int32_t>& rows, std::vector<std::int32_t>& cols) {
  auto line = std::string{};
  int row{0};
  rows.clear();
  cols.clear();
  while (std::getline(in, line)) {
    if (line.empty()) {
      break;
    }
    rows.emplace_back(0);
    if (cols.size() == 0) {
      cols.resize(line.size(), 0);
    }
    for (int col = 0; col < std::ssize(line); ++col) {
      if (line[col] == '#') {
        rows[row] |= (1 << col);
        cols[col] |= (1 << row);
      }
    }
    ++row;
  }
}

auto solve(std::ifstream& in, int tolerance) -> int {
  auto row_count = int{0}, col_count = int{0};
  auto rows = std::vector<std::int32_t>{};
  auto columns = std::vector<std::int32_t>{};
  rows.reserve(32);
  columns.reserve(32);

  while (!in.fail()) {
    GetMap(in, rows, columns);

    auto count = FindSymmetry(rows, tolerance);
    if (!count) {
      count = FindSymmetry(columns, tolerance);
      col_count += *count;
    } else {
      row_count += *count;
    }
  }

  return col_count + 100 * row_count;
}

}  // namespace

std::string Day13_1(std::ifstream& in) { return std::to_string(solve(in, 0)); };

std::string Day13_2(std::ifstream& in) { return std::to_string(solve(in, 1)); };
