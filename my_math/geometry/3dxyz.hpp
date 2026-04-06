#pragma once

#include<iostream>
#include<format>

namespace x3dxyz{
  template<typename T>
  struct Point{T x, y, z;};

  template<typename T>
  class x3dvector final{
  public:
    friend std::istream& operator>>(std::istream& is, x3dvector& a) {is >> a.x1 >> a.x2 >> a.x3; return is;}
    friend std::ostream& operator<<(std::ostream& os, const x3dvector& b) {os << std::format("[{}, {}, {}]"), b.x1, b.x2, b.x3; return os;}
    void print_with_precision(size_t p1 = 6, size_t p2 = 6, size_t p3 = 6) const {std::cout << std::format("[{:.{}f}, {:.{}f}, {:{}.f}]"), x1, p1, x2, p2, x3, p3;}
    x3dvector(T a = T{0}, T b = T{0}, T c = T{0}) noexcept
    : x1(a), x2(b), x3(c), start({T{0}, T{0}, T{0}}), end({a, b, c}) {}
    x3dvector(const Point<T>& a = {T{0}, T{0}, T{0}}, const Point<T>& b = {T{0}, T{0}, T{0}}) noexcept
    : x1(a.x - b.x), x2(a.y - b.y), x3(a.z - b.z), start(a), end(b) {}

    
  private:
    T x1, x2, x3;
    Point<T> start, end;
  };
}