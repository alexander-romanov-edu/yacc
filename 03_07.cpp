#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <print>
#include <utility>

template <typename T> class Vector {
public:
  Vector(std::size_t initial_capacity = 4)
      : m_array(new T[initial_capacity]{}), m_size(0),
        m_capacity(initial_capacity) {}

  Vector(std::initializer_list<T> list)
      : m_array(list.size() ? new T[list.size()]{} : nullptr),
        m_size(list.size()), m_capacity(list.size()) {
    std::ranges::copy(list, m_array);
  }

  Vector(const Vector &other)
      : m_array(other.m_capacity ? new T[other.m_capacity]{} : nullptr),
        m_size(other.m_size), m_capacity(other.m_capacity) {
    std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
  }

  Vector(Vector &&other) noexcept
      : m_array(std::exchange(other.m_array, nullptr)),
        m_size(std::exchange(other.m_size, 0)),
        m_capacity(std::exchange(other.m_capacity, 0)) {}

  ~Vector() { delete[] m_array; }

  Vector &operator=(Vector other) {
    std::println("Vector::operator=(copy/move)");
    swap(other);
    return *this;
  }

  void swap(Vector &other) {
    std::swap(m_array, other.m_array);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

  std::size_t size() const { return m_size; }
  std::size_t capacity() const { return m_capacity; }
  bool empty() const { return m_size == 0; }

  void clear() { m_size = 0; }

  void push_back(const T &value) {
    if (m_size == m_capacity) {
      grow();
    }
    m_array[m_size++] = value;
  }

private:
  T *m_array = nullptr;
  std::size_t m_size = 0;
  std::size_t m_capacity = 0;

  void grow() {
    std::size_t new_capacity = m_capacity ? m_capacity * 2 : 1;
    T *new_array = new T[new_capacity]{};
    if (m_size) {
      std::ranges::copy(m_array, m_array + m_size, new_array);
    }
    delete[] m_array;
    m_array = new_array;
    m_capacity = new_capacity;
  }
};

template <typename T> void swap(Vector<T> &lhs, Vector<T> &rhs) {
  lhs.swap(rhs);
}

int main() {
  Vector<int> v1; // default capacity allocated
  Vector<int> v2 = {1, 2, 3, 4, 5};

  std::println("v2 size = {}, capacity = {}", v2.size(), v2.capacity());

  v2.push_back(6);
  std::println("After push_back: v2 size = {}, capacity = {}", v2.size(),
               v2.capacity());

  v2.clear();
  std::println("After clear: v2 size = {}, empty = {}", v2.size(), v2.empty());
  v2 = {0, 2, 4, 3};

  Vector<int> v3 = v2;
  Vector<int> v4 = std::move(v3);
  std::println("v4 size = {}, empty = {}", v2.size(), v2.empty());

  v2 = {0, 2};
  v3 = v2;
  std::println("v3 size = {}, empty = {}", v2.size(), v2.empty());
  v4 = std::move(v3);

  swap(v1, v2);
  std::println("After swap: v1 size = {}, v2 size = {}", v1.size(), v2.size());
}
