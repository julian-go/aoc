#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

#include "common/problem.hpp"
#include "common/runner.hpp"
#include "solutions.hpp"

auto main(int argc, char *argv[]) -> int {
  auto num_runs = int{1};
  if (argc > 1) {
    num_runs = atoi(argv[1]);
  }

  const auto p = std::string{"inputs/year2021/"};
  auto problems = std::vector<aoc::Problem>{
      {"01-1-example", Day01_1, "7", p + "example-01.txt"},
      {"01-1-problem", Day01_1, "1521", p + "problem-01.txt"},
      {"01-2-example", Day01_2, "5", p + "example-01.txt"},
      {"01-2-problem", Day01_2, "1543", p + "problem-01.txt"},
      {"02-1-example", Day02_1, "", p + "example-02.txt"},
      {"02-1-problem", Day02_1, "", p + "problem-02.txt"},
      {"02-2-example", Day02_2, "", p + "example-02.txt"},
      {"02-2-problem", Day02_2, "", p + "problem-02.txt"},
      {"03-1-example", Day03_1, "", p + "example-03.txt"},
      {"03-1-problem", Day03_1, "", p + "problem-03.txt"},
      {"03-2-example", Day03_2, "", p + "example-03.txt"},
      {"03-2-problem", Day03_2, "", p + "problem-03.txt"},
      {"04-1-example", Day04_1, "", p + "example-04.txt"},
      {"04-1-problem", Day04_1, "", p + "problem-04.txt"},
      {"04-2-example", Day04_2, "", p + "example-04.txt"},
      {"04-2-problem", Day04_2, "", p + "problem-04.txt"},
      {"05-1-example", Day05_1, "", p + "example-05.txt"},
      {"05-1-problem", Day05_1, "", p + "problem-05.txt"},
      {"05-2-example", Day05_2, "", p + "example-05.txt"},
      {"05-2-problem", Day05_2, "", p + "problem-05.txt"},
      {"06-1-example", Day06_1, "", p + "example-06.txt"},
      {"06-1-problem", Day06_1, "", p + "problem-06.txt"},
      {"06-2-example", Day06_2, "", p + "example-06.txt"},
      {"06-2-problem", Day06_2, "", p + "problem-06.txt"},
      {"07-1-example", Day07_1, "", p + "example-07.txt"},
      {"07-1-problem", Day07_1, "", p + "problem-07.txt"},
      {"07-2-example", Day07_2, "", p + "example-07.txt"},
      {"07-2-example", Day07_2, "", p + "problem-07.txt"},
      {"08-1-example", Day08_1, "", p + "example-08.txt"},
      {"08-1-problem", Day08_1, "", p + "problem-08.txt"},
      {"08-2-example", Day08_2, "", p + "example-08.txt"},
      {"08-2-problem", Day08_2, "", p + "problem-08.txt"},
      {"09-1-example", Day09_1, "", p + "example-09.txt"},
      {"09-1-problem", Day09_1, "", p + "problem-09.txt"},
      {"09-2-example", Day09_2, "", p + "example-09.txt"},
      {"09-2-problem", Day09_2, "", p + "problem-09.txt"},
      {"10-1-example", Day10_1, "", p + "example-10.txt"},
      {"10-1-problem", Day10_1, "", p + "problem-10.txt"},
      {"10-2-example", Day10_2, "", p + "example-10.txt"},
      {"10-2-problem", Day10_2, "", p + "problem-10.txt"},
      {"11-1-example", Day11_1, "", p + "example-11.txt"},
      {"11-1-problem", Day11_1, "", p + "problem-11.txt"},
      {"11-2-example", Day11_2, "", p + "example-11.txt"},
      {"11-2-problem", Day11_2, "", p + "problem-11.txt"},
      {"12-1-example", Day12_1, "", p + "example-12.txt"},
      {"12-1-problem", Day12_1, "", p + "problem-12.txt"},
      {"12-2-example", Day12_2, "", p + "example-12.txt"},
      {"12-2-problem", Day12_2, "", p + "problem-12.txt"},
      {"13-1-example", Day13_1, "", p + "example-13.txt"},
      {"13-1-problem", Day13_1, "", p + "problem-13.txt"},
      {"13-2-example", Day13_2, "", p + "example-13.txt"},
      {"13-2-problem", Day13_2, "", p + "problem-13.txt"},
      {"14-1-example", Day14_1, "", p + "example-14.txt"},
      {"14-1-problem", Day14_1, "", p + "problem-14.txt"},
      {"14-2-example", Day14_2, "", p + "example-14.txt"},
      {"14-2-problem", Day14_2, "", p + "problem-14.txt"},
      {"15-1-example", Day15_1, "", p + "example-15.txt"},
      {"15-1-problem", Day15_1, "", p + "problem-15.txt"},
      {"15-2-example", Day15_2, "", p + "example-15.txt"},
      {"15-2-problem", Day15_2, "", p + "problem-15.txt"},
      {"16-1-example", Day16_1, "", p + "example-16.txt"},
      {"16-1-problem", Day16_1, "", p + "problem-16.txt"},
      {"16-2-example", Day16_2, "", p + "example-16.txt"},
      {"16-2-problem", Day16_2, "", p + "problem-16.txt"},
      {"17-1-example", Day17_1, "", p + "example-17.txt"},
      {"17-1-problem", Day17_1, "", p + "problem-17.txt"},
      {"17-2-example", Day17_2, "", p + "example-17.txt"},
      {"17-2-problem", Day17_2, "", p + "problem-17.txt"},
      {"18-1-example", Day18_1, "", p + "example-18.txt"},
      {"18-1-problem", Day18_1, "", p + "problem-18.txt"},
      {"18-2-example", Day18_2, "", p + "example-18.txt"},
      {"18-2-problem", Day18_2, "", p + "problem-18.txt"},
      {"19-1-example", Day19_1, "", p + "example-19.txt"},
      {"19-1-problem", Day19_1, "", p + "problem-19.txt"},
      {"19-2-example", Day19_2, "", p + "example-19.txt"},
      {"19-2-problem", Day19_2, "", p + "problem-19.txt"},
      {"20-1-example", Day20_1, "", p + "example-20.txt"},
      {"20-1-problem", Day20_1, "", p + "problem-20.txt"},
      {"20-2-example", Day20_2, "", p + "example-20.txt"},
      {"20-2-problem", Day20_2, "", p + "problem-20.txt"},
      {"21-1-example", Day21_1, "", p + "example-21.txt"},
      {"21-1-problem", Day21_1, "", p + "problem-21.txt"},
      {"21-2-example", Day21_2, "", p + "example-21.txt"},
      {"21-2-problem", Day21_2, "", p + "problem-21.txt"},
      {"22-1-example", Day22_1, "", p + "example-22.txt"},
      {"22-1-problem", Day22_1, "", p + "problem-22.txt"},
      {"22-2-example", Day22_2, "", p + "example-22.txt"},
      {"22-2-problem", Day22_2, "", p + "problem-22.txt"},
      {"23-1-example", Day23_1, "", p + "example-23.txt"},
      {"23-1-problem", Day23_1, "", p + "problem-23.txt"},
      {"23-2-example", Day23_2, "", p + "example-23.txt"},
      {"23-2-problem", Day23_2, "", p + "problem-23.txt"},
      {"24-1-example", Day24_1, "", p + "example-24.txt"},
      {"24-1-problem", Day24_1, "", p + "problem-24.txt"},
      {"24-2-example", Day24_2, "", p + "example-24.txt"},
      {"24-2-problem", Day24_2, "", p + "problem-24.txt"},
      {"25-1-example", Day25_1, "", p + "example-25.txt"},
      {"25-1-problem", Day25_1, "", p + "problem-25.txt"},
      {"25-2-example", Day25_2, "", p + "example-25.txt"},
      {"25-2-problem", Day25_2, "", p + "problem-25.txt"},
  };

  auto runner = aoc::Runner{problems, num_runs};
  runner.Run();

  return 0;
}