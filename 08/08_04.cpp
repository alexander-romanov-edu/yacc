#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iterator>
#include <print>
#include <random>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace {

constexpr std::string_view kChars = "abcdefghijklmnopqrstuvwxyz";
constexpr std::string_view kTarget = "ilovebigboobs";
constexpr std::size_t kStringsCount = 100;
constexpr unsigned kMutationProb = 5;

std::size_t countEqualChars(std::string_view first, std::string_view second) {
  return std::ranges::count_if(std::views::zip(first, second), [](auto pair) {
    auto [c1, c2] = pair;
    return c1 == c2;
  });
}

} // namespace

int main() try {
  std::random_device d;
  std::default_random_engine engine{d()};
  std::uniform_int_distribution<char> char_dist(0, kChars.size() - 1);
  std::uniform_int_distribution<unsigned> mutation_dist{0, 100};

  auto initial = [&] {
    std::string initial;
    initial.reserve(kTarget.size());
    std::generate_n(std::back_inserter(initial), kTarget.size(),
                    [&] { return kChars[char_dist(engine)]; });
    return initial;
  }();

  std::println("{}", initial);

  std::vector<std::string> strings;
  strings.resize(kStringsCount);

  for (;;) {
    std::ranges::generate(strings, [&] {
      std::string res = initial;
      for (char &c : res) {
        if (mutation_dist(engine) <= kMutationProb) {
          c = kChars[char_dist(engine)];
        }
      }
      return res;
    });

    auto scores =
        strings | std::views::transform([](std::string_view sv) static {
          return countEqualChars(sv, kTarget);
        });

    auto max_score_it = std::ranges::max_element(scores);

    std::println("{}", *max_score_it.base());

    if (*max_score_it == kTarget.size()) {
      break;
    }

    initial = *max_score_it.base();
  }
} catch (const std::exception &e) {
  std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(),
               e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println(stderr, "Caught an unknown exception");
  return EXIT_FAILURE;
}
