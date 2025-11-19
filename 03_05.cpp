#include <print>
#include <string>

class Entity_v1 {
public:
  virtual void test() const { std::print("Entity_v1::test\n"); }
  virtual ~Entity_v1() = default;
};

class Entity_v2 {
public:
  virtual void test() const { std::print("Entity_v2::test\n"); }
  virtual ~Entity_v2() = default;
};

class Adapter_v1 : public Entity_v1 {
public:
  virtual void test_v1() const = 0;

  void test() const override { test_v1(); }
};

class Adapter_v2 : public Entity_v2 {
public:
  virtual void test_v2() const = 0;

  void test() const override { test_v2(); }
};

class Client : public Adapter_v1, public Adapter_v2 {
public:
  void test_v1() const override { std::println("Client::test_v1"); }

  void test_v2() const override { std::println("Client::test_v2"); }
};

int main() {
  Client client;

  Entity_v1 *e1 = &client;
  Entity_v2 *e2 = &client;

  e1->test();
  e2->test();

  Adapter_v1 *a1 = &client;
  Adapter_v2 *a2 = &client;

  a1->test_v1();
  a2->test_v2();
}
