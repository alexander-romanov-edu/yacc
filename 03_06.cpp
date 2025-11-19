#include <cmath>
#include <concepts>
#include <memory>
#include <numbers>
#include <print>
#include <vector>

template <std::floating_point T> class Shape {
public:
  virtual ~Shape() = default;
  virtual T perimeter() const = 0;
  virtual T area() const = 0;
};

template <std::floating_point T> class Triangle final : public Shape<T> {
  T a, b, c;

public:
  Triangle(T aa, T bb, T cc) : a(aa), b(bb), c(cc) {}

  T perimeter() const override final { return a + b + c; }

  T area() const override final {
    const T p = perimeter() / T{2};
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
  }
};

template <std::floating_point T> class Square final : public Shape<T> {
  T side;

public:
  explicit Square(T s) : side(s) {}

  T perimeter() const override final { return T{4} * side; }

  T area() const override final { return side * side; }
};

template <std::floating_point T> class Circle final : public Shape<T> {
  T radius;

public:
  explicit Circle(T r) : radius(r) {}

  T perimeter() const override final {
    return T{2} * std::numbers::pi_v<T> * radius;
  }

  T area() const override final {
    return std::numbers::pi_v<T> * radius * radius;
  }
};

int main() {
  using T = double;
  std::vector<std::unique_ptr<Shape<T>>> shapes;

  shapes.push_back(std::make_unique<Triangle<T>>(3.0, 4.0, 5.0));
  shapes.push_back(std::make_unique<Square<T>>(2.0));
  shapes.push_back(std::make_unique<Circle<T>>(1.0));

  for (auto &shape : shapes) {
    std::println("Perimeter = {}, Area = {}", shape->perimeter(),
                 shape->area());
  }
}
