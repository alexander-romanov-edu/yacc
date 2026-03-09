#include <cassert>
#include <cmath>
#include <concepts>
#include <format>
#include <iostream>
#include <optional>
#include <print>
#include <stdexcept>
#include <variant>

namespace Comparison {

template <std::floating_point T> static constexpr T Epsilon = 1e-6;

template <std::floating_point T>
static constexpr bool isZero(T Value, T ZeroDiff = Epsilon<T>) {
  return std::abs(Value) < ZeroDiff;
}

} // namespace Comparison

namespace {

double fetchCoefficient(char Coefficient) {
  double Value{};
  std::cin >> Value;
  if (const auto StreamState = std::cin.rdstate();
      StreamState == std::ios_base::goodbit) {
    return Value;
  } else if (StreamState & std::ios_base::badbit) {
    throw std::runtime_error{std::format(
        "error occurred while reading coefficient \'{}\'", Coefficient)};
  } else if (StreamState & std::ios_base::eofbit) {
    if (!(StreamState & std::ios_base::failbit)) {
      return Value;
    }
  }
  throw std::runtime_error{std::format(
      "error occurred while reading coefficient \'{}\'", Coefficient)};
}

// Equation: b * x + c = 0, b != 0
double computeLinearRoot(double B, double C) {
  assert(!Comparison::isZero(B));
  return -C / B;
}

double normalizeToZero(double Value) {
  if (Comparison::isZero(Value)) {
    return 0.0;
  }
  return Value;
}

// Equation: a * x^2 + b * x + c = 0, a != 0
std::optional<std::pair<double, double>>
computeQuadraticRoots(double A, double B, double C) {
  assert(!Comparison::isZero(A));

  const auto Discriminant = normalizeToZero(B * B - 4 * A * C);
  if (Discriminant < 0) {
    return {};
  }

  const auto SqrtOfDiscriminant = std::sqrt(Discriminant);
  const auto DoubleA = 2 * A;
  const auto Root1 = (-B - SqrtOfDiscriminant) / DoubleA;
  const auto Root2 = (-B + SqrtOfDiscriminant) / DoubleA;
  return {{Root1, Root2}};
}

using InfiniteRoots = std::monostate;
using SingleRoot = double;
using DoubleRoots = std::pair<SingleRoot, SingleRoot>;

std::optional<std::variant<InfiniteRoots, SingleRoot, DoubleRoots>>
determineRoots(double A, double B, double C) {
  if (!Comparison::isZero(A)) {
    return computeQuadraticRoots(A, B, C).and_then(
        [](const auto &RootPair) static {
          using ReturnType = decltype(determineRoots(0, 0, 0));
          return ReturnType{RootPair};
        });
  }

  if (!Comparison::isZero(B)) {
    return computeLinearRoot(B, C);
  }

  if (Comparison::isZero(C)) {
    return std::monostate{};
  }

  return {};
}

} // unnamed namespace

int main() try {
  const auto CoefficientA = fetchCoefficient('a');
  const auto CoefficientB = fetchCoefficient('b');
  const auto CoefficientC = fetchCoefficient('c');

  if (const auto PossibleRoots =
          determineRoots(CoefficientA, CoefficientB, CoefficientC);
      !PossibleRoots.has_value()) {
    std::println("no roots");
  } else if (const auto &Roots = *PossibleRoots;
             std::holds_alternative<InfiniteRoots>(Roots)) {
    std::println("infinite number of roots");
  } else if (const auto *SRoot = std::get_if<SingleRoot>(&Roots)) {
    std::println("one root: {}", *SRoot);
  } else if (const auto *DRoots = std::get_if<DoubleRoots>(&Roots)) {
    std::println("two roots: ({:.2f}, {:.2f})", DRoots->first, DRoots->second);
  }
} catch (const std::exception &e) {
  std::println(stderr, "Caught an instance of {}.\nwhat(): {}",
               typeid(e).name(), e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println(stderr, "Caught an unknown exception.");
  return EXIT_FAILURE;
}
