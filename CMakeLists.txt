cmake_minimum_required(VERSION 3.26)

cmake_policy(VERSION 3.26)

project(
  AOC2022
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/spdlog)
add_subdirectory(lib/magic_enum)

set(COMMON_SRCS 
        src/common/display.cpp 
        src/common/runner.cpp
)

set(Y2022_SRCS 
        src/year2022/main.cpp
        src/year2022/day01/solution.cpp
        src/year2022/day02/solution.cpp
        src/year2022/day03/solution.cpp
        src/year2022/day04/solution.cpp
        src/year2022/day05/solution.cpp
        src/year2022/day06/solution.cpp
        src/year2022/day07/solution.cpp
        src/year2022/day08/solution.cpp
        src/year2022/day09/solution.cpp
        src/year2022/day10/solution.cpp
        src/year2022/day11/solution.cpp
        src/year2022/day12/solution.cpp
        src/year2022/day13/solution.cpp
        src/year2022/day14/solution.cpp
        src/year2022/day15/solution.cpp
        src/year2022/day16/solution.cpp
        src/year2022/day17/solution.cpp
        src/year2022/day18/solution.cpp
        src/year2022/day19/solution.cpp
        src/year2022/day20/solution.cpp
        src/year2022/day21/solution.cpp
        src/year2022/day22/solution.cpp
        src/year2022/day23/solution.cpp
        src/year2022/day24/solution.cpp
        src/year2022/day25/solution.cpp
)

add_executable(AOC2022 ${Y2022_SRCS} ${COMMON_SRCS})

set(LIBS spdlog::spdlog magic_enum::magic_enum)

target_link_libraries(AOC2022 PRIVATE ${LIBS})

target_include_directories(AOC2022 PRIVATE include/)