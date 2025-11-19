#include <print>
#include <stdexcept>
#include <string>

template <typename T> class List {
private:
  struct Node {
    T value;
    Node *next = nullptr;

    Node(const T &val) : value(val) {}
  };

  Node *head = nullptr;
  Node *tail = nullptr;

public:
  ~List() {
    while (head) {
      pop_front();
    }
  }

  bool empty() const { return head == nullptr; }

  void show() const {
    for (auto curr = head; curr; curr = curr->next) {
      std::print("{} ", curr->value);
    }
    std::print("\n");
  }

  void push_front(const T &val) {
    auto node = new Node(val);
    node->next = head;
    head = node;
    if (!tail)
      tail = head;
  }

  void push_back(const T &val) {
    auto node = new Node(val);
    if (tail) {
      tail->next = node;
      tail = node;
    } else {
      head = tail = node;
    }
  }

  void pop_front() {
    if (!head)
      return;
    auto tmp = head;
    head = head->next;
    delete tmp;
    if (!head)
      tail = nullptr;
  }

  void pop_back() {
    if (!head)
      return;

    if (head == tail) {
      delete head;
      head = tail = nullptr;
      return;
    }

    auto curr = head;
    while (curr->next != tail) {
      curr = curr->next;
    }
    delete tail;
    tail = curr;
    tail->next = nullptr;
  }

  T get() const {
    if (!head)
      throw std::runtime_error("List is empty");

    Node *slow = head;
    Node *fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow->value;
  }
};

int main() try {
  List<int> lst;

  std::print("Empty? {}\n", lst.empty());

  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  lst.push_front(5);

  std::print("List: ");
  lst.show();

  std::print("Middle value: {}\n", lst.get());

  lst.pop_front();
  std::print("After pop_front: ");
  lst.show();

  lst.pop_back();
  std::print("After pop_back: ");
  lst.show();

  std::print("Empty? {}\n", lst.empty());

  List<std::string> strList;
  strList.push_back("hello");
  strList.push_back("world");
  strList.push_back("template");

  std::print("String list: ");
  strList.show();
  std::print("Middle string: {}\n", strList.get());
} catch (const std::exception &e) {
  std::print("Exception: {}\n", e.what());
  return 1;
}
