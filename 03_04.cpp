#include <print>

class Entity {
private:
  void test_v1() const { std::println("Entity::test_v1 executed"); }

  void test_v2() const { std::println("Entity::test_v2 executed"); }

public:
  struct Attorney {
    friend class Tester_v1;
    friend class Tester_v2;

  private:
    static void call_v1(const Entity &e) { e.test_v1(); }

    static void call_v2(const Entity &e) { e.test_v2(); }
  };
};

class Tester_v1 {
public:
  void run(const Entity &e) { Entity::Attorney::call_v1(e); }
};

class Tester_v2 {
public:
  void run(const Entity &e) { Entity::Attorney::call_v2(e); }
};

int main() {
  Entity e;
  Tester_v1 t1;
  Tester_v2 t2;

  t1.run(e);
  t2.run(e);
}
