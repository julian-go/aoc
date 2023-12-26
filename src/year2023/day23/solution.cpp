#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "common/matrix_2d.hpp"
#include "common/utils.hpp"
#include "common/vector_2d.hpp"
#include "solutions.hpp"

namespace {

enum class Type { kEmpty, kWall, kNorthRamp, kSouthRamp, kEastRamp, kWestRamp };

using Cache = aoc::Matrix2D<int>;
using Coordinate = aoc::Vector2D<int>;
using CoordinateSet = std::unordered_set<Coordinate, Coordinate::Hash>;
using Map = aoc::Matrix2D<Type>;

struct Node {
  Coordinate id;
  std::vector<std::pair<Coordinate, int>> neighbors;
  bool blocked;
  bool IsTunnel() { return std::ssize(neighbors) == 2; }
  bool IsCulDeSac() { return std::ssize(neighbors) == 1; }
};

using Graph = std::unordered_map<Coordinate, Node, Coordinate::Hash>;

struct Problem {
  Graph graph;
  Coordinate goal;
};

auto GetProblem(std::ifstream& in) -> std::tuple<Map, Coordinate, Coordinate> {
  auto [max_x, max_y] = aoc::size(in);
  auto map = aoc::Matrix2D<Type>(max_x, max_y);
  auto start = Coordinate{-1, -1};
  auto goal = Coordinate{-1, -1};
  auto line = std::string{};
  int y{0};
  while (std::getline(in, line)) {
    int x{0};
    for (const auto& c : line) {
      switch (c) {
        case '.':
          if (y == 0) {
            start = {x, y};
          } else if (y == max_y - 1) {
            goal = {x, y};
          }
          map.at(x, y) = Type::kEmpty;
          break;
        case '#':
          map.at(x, y) = Type::kWall;
          break;
        case '^':
          map.at(x, y) = Type::kNorthRamp;
          break;
        case 'v':
          map.at(x, y) = Type::kSouthRamp;
          break;
        case '>':
          map.at(x, y) = Type::kEastRamp;
          break;
        case '<':
          map.at(x, y) = Type::kWestRamp;
          break;
      }
      ++x;
    }
    ++y;
  }
  return {map, start, goal};
}

template <bool IgnoreIce>
auto NodesFromMap(const Map& map) -> Graph {
  auto nodes = Graph{};
  for (auto y = 0; y < map.sizeX(); ++y) {
    for (auto x = 0; x < map.sizeY(); ++x) {
      auto xy = Coordinate{x, y};
      if (map.at(xy) == Type::kWall) {
        continue;
      }
      auto node = Node{xy, {}, false};
      if (map.at(xy) != Type::kEmpty && !IgnoreIce) {
        node.blocked = true;
      }
      for (auto n : xy.Neighbors()) {
        if (!map.contains(n)) {
          continue;
        }

        bool blocked = map.at(n) == Type::kWall;
        if constexpr (!IgnoreIce) {
          blocked = blocked || (map.at(n) == Type::kNorthRamp && n != xy.North());
          blocked = blocked || (map.at(n) == Type::kSouthRamp && n != xy.South());
          blocked = blocked || (map.at(n) == Type::kEastRamp && n != xy.East());
          blocked = blocked || (map.at(n) == Type::kWestRamp && n != xy.West());
        }
        if (blocked) {
          if (map.at(n) != Type::kWall) node.blocked = true;
          continue;
        }

        node.neighbors.emplace_back(n, 1);
      }
      nodes.emplace(xy, node);
    }
  }
  return nodes;
}

void Contract(Graph& g) {
  bool done = false;
  while (!done) {
    done = true;
    for (auto& [id, node] : g) {
      if (node.IsTunnel() && !node.blocked) {
        auto [n1, d1] = node.neighbors[0];
        auto [n2, d2] = node.neighbors[1];
        g.at(n1).neighbors.emplace_back(n2, d1 + d2);
        g.at(n2).neighbors.emplace_back(n1, d1 + d2);
        std::erase_if(g.at(n1).neighbors, [&](auto& p) { return p.first == id; });
        std::erase_if(g.at(n2).neighbors, [&](auto& p) { return p.first == id; });
        node.neighbors.clear();
        done = false;
      }
    }
  }
  std::erase_if(g, [](auto& p) { return p.second.neighbors.empty(); });
}

using TerminalSet = std::deque<Coordinate>;

auto g(const Problem& p, CoordinateSet visited, Coordinate c) -> std::tuple<int, TerminalSet> {
  if (c == p.goal) {
    return {0, {c}};
  }

  visited.insert(c);

  auto node = p.graph.at(c);
  int cost = std::numeric_limits<int>::min();
  TerminalSet terminal_set{};
  for (const auto& [n, d] : node.neighbors) {
    if (visited.contains(n)) {
      continue;
    }
    auto [distance, nodes] = g(p, visited, n);
    if (d + distance > cost) {
      cost = d + distance;
      terminal_set = nodes;
    }
  }
  terminal_set.push_front(c);
  return {cost, terminal_set};
}

}  // namespace

std::string Day23_1(std::ifstream& in) {
  auto [map, start, stop] = GetProblem(in);
  auto nodes = NodesFromMap<false>(map);
  Contract(nodes);
  auto problem = Problem{nodes, stop};
  auto [result, terminal_set] = g(problem, {}, start);
  // for (auto& c : terminal_set) {
  //   std::cout << c << "\n";
  // }
  // for (auto& [id, node] : nodes) {
  //   std::cout << id << " to ";
  //   for (auto& [n, d] : node.neighbors) {
  //     std::cout << n << ":" << d << "; ";
  //   }
  //   std::cout << "\n";
  // }
  return std::to_string(result);
};

std::string Day23_2(std::ifstream& in) {
  auto [map, start, stop] = GetProblem(in);
  auto nodes = NodesFromMap<true>(map);
  Contract(nodes);
  auto problem = Problem{nodes, stop};
  auto [result, terminal_set] = g(problem, {}, start);
  return std::to_string(result);
};