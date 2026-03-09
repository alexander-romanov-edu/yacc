#include <cstdio>
#include <cstdlib>
#include <exception>
#include <memory_resource>
#include <print>

int main() try {
  static_cast<void>(std::pmr::null_memory_resource()->allocate(1));
} catch (const std::exception &e) {
  std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(),
               e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println(stderr, "Caught an unknown exception");
  return EXIT_FAILURE;
}
