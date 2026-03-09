#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <print>
#include <stdexcept>

#include <boost/dll.hpp>

#include "06_05_shared.hpp"

int main() try {
  boost::dll::fs::path path;
  std::cin >> path;
  if (!std::cin.good()) {
    throw std::runtime_error{"could not read the path to the shared library"};
  }

  const auto lib = boost::dll::import_symbol<decltype(::test)>(path, "test");

  std::println("test() == {}", lib());
} catch (const std::exception &e) {
  std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(),
               e.what());
  return EXIT_FAILURE;
} catch (...) {
  std::println(stderr, "Caught an unknown exception");
  return EXIT_FAILURE;
}
