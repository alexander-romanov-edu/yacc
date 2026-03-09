#include <cstdio>
#include <exception>
#include <print>
#include <vector>

int main() try {
  std::vector<int> v;
  v.reserve(v.max_size() + 1);
} catch (const std::exception &e) {
  std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(),
               e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println(stderr, "Caught an unknown exception");
  return EXIT_FAILURE;
}
