#include <algorithm>
#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

#include "common/interval.hpp"
#include "solutions.hpp"

struct IntervalMap {
  std::int64_t from = 0;
  std::int64_t to = 0;
  std::int64_t length = 0;

  auto map(aoc::Interval rhs) const -> std::tuple<aoc::Interval, std::vector<aoc::Interval>> {
    auto mapped = aoc::Interval{0, 0};
    mapped = aoc::Intersection(rhs, aoc::Interval{from, from + length});
    mapped += (to - from);

    auto remainder = aoc::Difference(rhs, aoc::Interval{from, from + length});

    return {mapped, remainder};
  }
};

struct Almanac {
  std::vector<aoc::Interval> seeds;
  std::vector<std::vector<IntervalMap>> maps;
};

auto GetAlmanac(std::ifstream& in, int part) -> Almanac {
  auto almanac = Almanac{};
  auto line = std::string{};

  in.ignore(10, ':');

  {
    std::getline(in, line);
    auto ss = std::stringstream{line};
    auto from = std::int64_t{0};
    auto length = std::int64_t{0};
    while (ss >> from >> length) {
      if (part == 1) {
        almanac.seeds.emplace_back(from, from + 1);
        almanac.seeds.emplace_back(length, length + 1);
      } else {
        almanac.seeds.emplace_back(from, from + length);
      }
    }
  } 

  in.ignore();  // skip one line

  while (std::getline(in, line)) {
    auto maps = std::vector<IntervalMap>{};
    while (std::getline(in, line) && !line.empty()) {
      auto ss = std::stringstream{line};
      maps.emplace_back();
      ss >> maps.back().to >> maps.back().from >> maps.back().length;
    }
    almanac.maps.push_back(maps);
  }
  return almanac;
}

void MapAlmanac(Almanac& almanac) {
  for (const auto& map_set : almanac.maps) {
    auto mapped_seeds = std::vector<aoc::Interval>{};
    // We iterate over all seeds, mapping the using the map function. The "remainder" of the
    // interval is returned. We do this to keep track of the seeds that are not mapped in the
    // current stage, since they keep their current value.
    for (const auto& map : map_set) {
      auto seeds = almanac.seeds;
      almanac.seeds.clear();
      while (!seeds.empty()) {
        auto [mapped, remainder] = map.map(seeds.back());
        seeds.pop_back();
        if (!mapped.empty()) {
          mapped_seeds.push_back(mapped);
        }
        std::move(remainder.begin(), remainder.end(), std::back_inserter(almanac.seeds));
      }
    }
    std::move(mapped_seeds.begin(), mapped_seeds.end(), std::back_inserter(almanac.seeds));
  }
}

std::string Day05_1(std::ifstream& in) {
  auto almanac = GetAlmanac(in, 1);
  MapAlmanac(almanac);
  auto result = std::min_element(almanac.seeds.begin(), almanac.seeds.end())->start;
  return std::to_string(result);
};

std::string Day05_2(std::ifstream& in) {
  auto almanac = GetAlmanac(in, 2);
  MapAlmanac(almanac);
  auto result = std::min_element(almanac.seeds.begin(), almanac.seeds.end())->start;
  return std::to_string(result);
};