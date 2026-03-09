#include <cstdio>
#include <cstdlib>
#include <exception>
#include <print>
#include <vector>

int main() try {
  const std::vector<int> v{1, 2, 3, 4, 5};
  std::println("{}", v.at(42));
} catch (const std::exception &e) {
  std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(),
               e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println(stderr, "Caught an unknown exception");
  return EXIT_FAILURE;
}
