#ifndef AOC_COMMON_VECTOR_2D_H_
#define AOC_COMMON_VECTOR_2D_H_

#include <array>
#include <cstdint>
#include <iostream>

namespace aoc {

struct Vector2D {
  struct Hash {
    std::size_t operator()(const Vector2D& v) const {
      return static_cast<std::uint64_t>(v.x) << 32 | static_cast<std::uint64_t>(v.y);
    }
  };

  constexpr Vector2D() : x(0), y(0){};
  constexpr Vector2D(int x, int y) : x(x), y(y){};
  constexpr virtual ~Vector2D() = default;

  int length() const { return std::abs(x) + std::abs(y); }
  int manhattan() const { return std::abs(x) + std::abs(y); }

  void RotateRight() {
    int tmp = x;
    x = -y;
    y = tmp;
  }

  void RotateLeft() {
    int tmp = x;
    x = y;
    y = -tmp;
  }

  Vector2D Right() { return {-y, x}; }
  Vector2D Left() { return {y, -x}; }

  auto Neighbors() const -> std::array<Vector2D, 4> { return {North(), South(), East(), West()}; }
  const Vector2D& North() const { return *this + Vector2D(0, -1); }
  const Vector2D& South() const { return *this + Vector2D(0, 1); }
  const Vector2D& East() const { return *this + Vector2D(1, 0); }
  const Vector2D& West() const { return *this + Vector2D(-1, 0); }

  Vector2D operator*(const int& r) const { return Vector2D(x * r, y * r); }

  Vector2D operator+(const Vector2D& r) const { return Vector2D(x + r.x, y + r.y); }

  Vector2D& operator+=(const Vector2D& r) {
    x += r.x;
    y += r.y;
    return *this;
  }

  Vector2D operator-(const Vector2D& r) const { return Vector2D(x - r.x, y - r.y); }

  inline bool operator==(const Vector2D& r) const { return x == r.x && y == r.y; }

  inline bool operator<(const Vector2D& r) const {
    if (x < r.x) {
      return true;
    } else if (x == r.x) {
      return y < r.y;
    } else {
      return false;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
    out << "(" << v.x << "," << v.y << ")";
    return out;
  }

  int x;
  int y;
};

inline auto Manhattan(Vector2D v1, Vector2D v2) -> int { return (v1 - v2).length(); }

}  // namespace aoc

#endif  // !AOC_COMMON_VECTOR_2D_H_