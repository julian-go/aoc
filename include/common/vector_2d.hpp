#ifndef AOC_COMMON_VECTOR_2D_H_
#define AOC_COMMON_VECTOR_2D_H_

#include <iostream>

namespace aoc {

template <typename TType = int>
struct Vector2D {
  constexpr Vector2D() : x(0), y(0){};
  constexpr Vector2D(TType x, TType y) : x(x), y(y){};
  constexpr virtual ~Vector2D() = default;

  int length() const { return std::abs(x) + std::abs(y); }
  int manhattan() const { return std::abs(x) + std::abs(y); }

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

  TType x;
  TType y;
};

}  // namespace aoc

#endif  // !AOC_COMMON_VECTOR_2D_H_