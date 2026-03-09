#include <cstdio>
#include <cstdlib>
#include <exception>
#include <optional>
#include <print>
#include <string>

int main() try {
  const std::optional<std::string> maybe_string;
  std::println("{}", maybe_string.value());
} catch (const std::exception &e) {
  std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(),
               e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println(stderr, "Caught an unknown exception");
  return EXIT_FAILURE;
}
