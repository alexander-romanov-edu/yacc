#include <print>
#include <type_traits>

class Entity_v1 {
private:
  int x = 42;
};

class Entity_v2 {
public:
  int x;
};

union Entity {
  Entity_v1 e1;
  Entity_v2 e2;
};

int main() {
  // Solution 1
  {
    Entity_v1 e;
    std::println("{}", reinterpret_cast<Entity_v2 &>(e).x); // UB
    reinterpret_cast<Entity_v2 &>(e).x = 43;                // UB
    std::println("{}", reinterpret_cast<Entity_v2 &>(e).x);
  }

  // Solution 2
  {
    static_assert(std::is_standard_layout_v<Entity_v1>);
    static_assert(std::is_standard_layout_v<Entity_v2>);
    static_assert(std::is_standard_layout_v<Entity>);

    Entity u{.e1 = Entity_v1{}};
    std::println("{}", u.e2.x); // OK
    u.e2.x = 43;                // OK
    std::println("{}", u.e2.x);
  }
}
