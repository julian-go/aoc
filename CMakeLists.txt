cmake_minimum_required(VERSION 3.26)

cmake_policy(VERSION 3.26)

project(
  AOC
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

set(Y2021_SRCS 
        src/year2021/main.cpp
        src/year2021/day01/solution.cpp
        src/year2021/day02/solution.cpp
        src/year2021/day03/solution.cpp
        src/year2021/day04/solution.cpp
        src/year2021/day05/solution.cpp
        src/year2021/day06/solution.cpp
        src/year2021/day07/solution.cpp
        src/year2021/day08/solution.cpp
        src/year2021/day09/solution.cpp
        src/year2021/day10/solution.cpp
        src/year2021/day11/solution.cpp
        src/year2021/day12/solution.cpp
        src/year2021/day13/solution.cpp
        src/year2021/day14/solution.cpp
        src/year2021/day15/solution.cpp
        src/year2021/day16/solution.cpp
        src/year2021/day17/solution.cpp
        src/year2021/day18/solution.cpp
        src/year2021/day19/solution.cpp
        src/year2021/day20/solution.cpp
        src/year2021/day21/solution.cpp
        src/year2021/day22/solution.cpp
        src/year2021/day23/solution.cpp
        src/year2021/day24/solution.cpp
        src/year2021/day25/solution.cpp
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

set(Y2023_SRCS 
        src/year2023/main.cpp
        src/year2023/day01/solution.cpp
        src/year2023/day02/solution.cpp
        src/year2023/day03/solution.cpp
        src/year2023/day04/solution.cpp
        src/year2023/day05/solution.cpp
        src/year2023/day06/solution.cpp
        src/year2023/day07/solution.cpp
        src/year2023/day08/solution.cpp
        src/year2023/day09/solution.cpp
        src/year2023/day10/solution.cpp
        src/year2023/day11/solution.cpp
        src/year2023/day12/solution.cpp
        src/year2023/day13/solution.cpp
        src/year2023/day14/solution.cpp
        src/year2023/day15/solution.cpp
        src/year2023/day16/solution.cpp
        src/year2023/day17/solution.cpp
        src/year2023/day18/solution.cpp
        src/year2023/day19/solution.cpp
        src/year2023/day20/solution.cpp
        src/year2023/day21/solution.cpp
        src/year2023/day22/solution.cpp
        src/year2023/day23/solution.cpp
        src/year2023/day24/solution.cpp
        src/year2023/day25/solution.cpp
)

add_executable(AOC2021 ${Y2021_SRCS} ${COMMON_SRCS})
add_executable(AOC2022 ${Y2022_SRCS} ${COMMON_SRCS})
add_executable(AOC2023 ${Y2023_SRCS} ${COMMON_SRCS})

set(LIBS spdlog::spdlog magic_enum::magic_enum)

target_link_libraries(AOC2021 PRIVATE ${LIBS})
target_link_libraries(AOC2022 PRIVATE ${LIBS})
target_link_libraries(AOC2023 PRIVATE ${LIBS})

target_include_directories(AOC2021 PRIVATE include/)
target_include_directories(AOC2022 PRIVATE include/)
target_include_directories(AOC2023 PRIVATE include/)