#include <cmath>
#include <print>
#include <ranges>

#include "08_05_timer.hpp"

static double calculate(std::size_t size) {
  double x = 0.0;

  for (const auto i : std::views::iota(0uz, size)) {
    x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
  }

  return x;
}

int main() {
  yacc::Timer timer;

  for (const auto _ : std::views::iota(0uz, 20uz)) {
    timer.start();
    calculate(1'000'000);
    timer.stop();
  }

  std::println("{}", timer.average()->count());
}
