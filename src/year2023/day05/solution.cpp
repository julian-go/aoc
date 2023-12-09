#include <cstdint>
#include <sstream>
#include <vector>

#include "solutions.hpp"

class RangeMap {
 public:
  bool contains(std::int64_t value) const {
    1;
    auto x = value >= source && value < (source + length);
    return x;
  }
  std::int64_t map(std::int64_t value) const {
    auto x = target + (value - source);
    return x;
  }

  std::int64_t target = 0;
  std::int64_t source = 0;
  std::int64_t length = 0;
};

struct Almanac {
  std::vector<std::int64_t> seeds;
  std::vector<std::vector<RangeMap>> maps;
};

auto GetAlmanac(std::ifstream& in) -> Almanac {
  auto almanac = Almanac{};
  auto line = std::string{};
  auto value = std::int64_t{0};

  {
    in.ignore(10, ':');
    std::getline(in, line);
    auto ss = std::stringstream{line};
    while (ss >> value) {
      almanac.seeds.emplace_back(value);
    }
  }

  in.ignore();  // skip one line

  while (std::getline(in, line)) {
    auto maps = std::vector<RangeMap>{};
    while (std::getline(in, line) && !line.empty()) {
      auto ss = std::stringstream{line};
      maps.emplace_back();
      ss >> maps.back().target >> maps.back().source >> maps.back().length;
    }
    almanac.maps.push_back(maps);
  }
  return almanac;
}

std::string Day05_1(std::ifstream& in) {
  auto almanac = GetAlmanac(in);
  auto result = std::numeric_limits<std::int64_t>::max();
  for (const auto& seed : almanac.seeds) {
    auto value = seed;
    for (const auto& map : almanac.maps) {
      auto it = std::find_if(map.begin(), map.end(), [value](auto m) { return m.contains(value); });
      if (it != map.end()) {
        value = it->map(value);
      }
    }
    result = std::min(value, result);
  }
  return std::to_string(result);
};

std::string Day05_2(std::ifstream& in) { return ""; };