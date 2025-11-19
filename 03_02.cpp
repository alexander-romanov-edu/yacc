#include <cmath>
#include <concepts>
#include <numbers>
#include <print>

template <std::floating_point T> class Triangle {
  T a, b, c;

public:
  Triangle(T aa, T bb, T cc) : a(aa), b(bb), c(cc) {}

  T perimeter() const { return a + b + c; }

  T area() const {
    const T p = perimeter() / T{2};
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
  }
};

template <std::floating_point T> class Square {
  T side;

public:
  explicit Square(T s) : side(s) {}

  T perimeter() const { return T{4} * side; }

  T area() const { return side * side; }
};

template <std::floating_point T> class Circle {
  T radius;

public:
  explicit Circle(T r) : radius(r) {}

  T perimeter() const { return T{2} * std::numbers::pi_v<T> * radius; }

  T area() const { return std::numbers::pi_v<T> * radius * radius; }
};

int main() {
  Triangle<double> t{3.0, 4.0, 5.0};
  Square<double> s{2.0};
  Circle<double> c{1.0};

  std::println("Triangle: perimeter = {}, area = {}", t.perimeter(), t.area());
  std::println("Square:   perimeter = {}, area = {}", s.perimeter(), s.area());
  std::println("Circle:   perimeter = {}, area = {}", c.perimeter(), c.area());
}
