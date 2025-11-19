#include "03_07.hpp"

#include <print>

int main() {
  yacc::Vector<int> v1; // default capacity allocated
  yacc::Vector<int> v2 = {1, 2, 3, 4, 5};

  std::println("v2 size = {}, capacity = {}", v2.size(), v2.capacity());

  v2.push_back(6);
  std::println("After push_back: v2 size = {}, capacity = {}", v2.size(),
               v2.capacity());

  v2.clear();
  std::println("After clear: v2 size = {}, empty = {}", v2.size(), v2.empty());
  v2 = {0, 2, 4, 3};

  yacc::Vector<int> v3 = v2;
  yacc::Vector<int> v4 = std::move(v3);
  std::println("v4 size = {}, empty = {}", v2.size(), v2.empty());

  v2 = {0, 2};
  v3 = v2;
  std::println("v3 size = {}, empty = {}", v2.size(), v2.empty());
  v4 = std::move(v3);

  swap(v1, v2);
  std::println("After swap: v1 size = {}, v2 size = {}", v1.size(), v2.size());
}
