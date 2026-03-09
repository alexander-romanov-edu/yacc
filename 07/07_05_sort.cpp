#include <charconv>
#include <cstdlib>
#include <format>
#include <ranges>
#include <string_view>
#include <vector>

#include "benchmark/benchmark.h"

#include "07_05_sort.hpp"

class SortBenchmark : public benchmark::Fixture {
public:
  SortBenchmark() {
    const char *env_var = std::getenv("SORT_THRESHOLD");
    if (!env_var) {
      throw std::runtime_error{
          std::format("SORT_THRESHOLD environment variable is not set")};
    }

    const std::string_view env_sv{env_var};
    const auto [ptr, ec] = std::from_chars(
        env_sv.data(), env_sv.data() + env_sv.size(), threshold_);
    if (ec == std::errc::invalid_argument) {
      throw std::runtime_error{
          std::format("could not parse std::size_t from \'{}\'", env_sv)};
    } else if (ec == std::errc::result_out_of_range) {
      throw std::runtime_error{std::format("\'{}\' is out of range", env_sv)};
    } else if (ptr != env_sv.data() + env_sv.size()) {
      throw std::runtime_error{
          std::format("unparsed characters in string \'{}\'", env_sv)};
    }
  }

  std::size_t threshold() const noexcept { return threshold_; }

private:
  std::size_t threshold_;
};

BENCHMARK_F(SortBenchmark, run)(benchmark::State &state) {
  constexpr int kSize = 10'000;
  constexpr auto kRange = std::views::iota(0, kSize) | std::views::reverse;
  static_assert(kRange.size() == kSize);
  std::vector<int> v(kSize);
  for (auto _ : state) {
    std::ranges::copy(kRange, v.begin());
    dts::sort(v.begin(), v.end(), threshold());
  }
}

BENCHMARK_MAIN();
