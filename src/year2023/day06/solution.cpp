#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>

#include "solutions.hpp"

auto GetTimesAndRecords(std::ifstream& in) -> std::tuple<std::vector<int>, std::vector<int>> {
  auto line = std::string{};
  auto times = std::vector<int>{};
  auto records = std::vector<int>{};
  {
    in.ignore(10, ':');
    std::getline(in, line);
    auto ss = std::stringstream{line};
    auto time = int{};
    while (ss >> time) {
      times.push_back(time);
    }
  }
  {
    in.ignore(10, ':');
    std::getline(in, line);
    auto ss = std::stringstream{line};
    auto record = int{};
    while (ss >> record) {
      records.push_back(record);
    }
  }
  return {times, records};
}

auto GetTimeAndRecord(std::ifstream& in) -> std::tuple<std::int64_t, std::int64_t> {
  auto line = std::string{};
  auto time = std::int64_t{};
  auto record = std::int64_t{};
  {
    in.ignore(10, ':');
    std::getline(in, line);
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    time = std::stoll(line);
  }
  {
    in.ignore(10, ':');
    std::getline(in, line);
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    record = std::stoll(line);
  }
  return {time, record};
}
std::string Day06_1(std::ifstream& in) {
  auto [times, records] = GetTimesAndRecords(in);
  auto result = int{1};
  for (auto t = times.begin(), r = records.begin(); t != times.end() && r != records.end();
       ++t, ++r) {
    // Need to be one better than the record, hence *r + 1
    double upper_bound = *t / 2.0 + std::sqrt((*t) * (*t) / 4.0 - (*r + 1));
    double lower_bound = *t / 2.0 - std::sqrt((*t) * (*t) / 4.0 - (*r + 1));
    result *= 1 + std::floor(upper_bound) - std::ceil(lower_bound);
  }
  return std::to_string(result);
};

std::string Day06_2(std::ifstream& in) {
  auto [time, record] = GetTimeAndRecord(in);

  double upper_bound = time / 2.0 + std::sqrt(time * time / 4.0 - (record + 1));
  double lower_bound = time / 2.0 - std::sqrt(time * time / 4.0 - (record + 1));
  std::int64_t result = 1 + std::floor(upper_bound) - std::ceil(lower_bound);

  return std::to_string(result);
};