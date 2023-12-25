#include <queue>
#include <sstream>

#include "common/matrix_nd.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

using int_t = std::int64_t;
using Vector = aoc::Vector2D<int_t>;

auto GetOffset(std::ifstream& in) {
  auto line = std::string{};
  auto offset = Vector{};
  char dir{};
  int steps{0};

  in >> dir >> steps;
  std::getline(in, line);

  switch (dir) {
    case 'R':
      offset = {steps, 0};
      break;
    case 'D':
      offset = {0, steps};
      break;
    case 'L':
      offset = {-steps, 0};
      break;
    case 'U':
      offset = {0, -steps};
      break;
  }

  return offset;
}

auto GetHexOffset(std::ifstream& in) {
  auto offset = Vector{};
  auto line = std::string{};
  std::getline(in, line, '#');
  std::getline(in, line, ')');
  if (line.empty()) {
    return offset;
  }
  int dir = line.back() - '0';
  line.pop_back();
  int steps{0};
  auto ss = std::stringstream{line};
  ss >> std::hex >> steps;
  switch (dir) {
    case 0:
      offset = {steps, 0};
      break;
    case 1:
      offset = {0, steps};
      break;
    case 2:
      offset = {-steps, 0};
      break;
    case 3:
      offset = {0, -steps};
      break;
  }

  return offset;
}


// This problem can be solved using the shoelace formula and Pick's theorem.
// First the shoelace formula [1] is used to calculate the area of the polygon.
// Then Pick's theorem [2] is used to calculate the area of the polygon using the following formula:
//   A = i + b/2 - 1
// where i is the number of points inside the polygon and b is the number of points on the boundary.
// Rearranging the formula gives:
// i + b = A + b/2 + 1
//
// [1] https://en.wikipedia.org/wiki/Shoelace_formula
// [2] https://en.wikipedia.org/wiki/Pick%27s_theorem

template <typename Predicate>
auto Solve(std::ifstream& in, Predicate get_offset) -> int_t {
  auto last = Vector{};
  int_t area{0};
  int_t boundary{0};
  while (!in.fail()) {
    const auto current = last + get_offset(in);
    area += (last.y + current.y) * (last.x - current.x);
    boundary += std::abs(current.x - last.x) + std::abs(current.y - last.y);
    last = current;
  }
  area /= 2;
  int_t result = area + boundary / 2 + 1;
  return result;
}

}  // namespace

std::string Day18_1(std::ifstream& in) {
  return std::to_string(Solve(in, GetOffset));
};

std::string Day18_2(std::ifstream& in) {
  return std::to_string(Solve(in, GetHexOffset));
}