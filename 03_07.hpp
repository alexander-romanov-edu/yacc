# pragma once

#include <utility>
#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <iterator>

namespace yacc {
template <typename T> class Vector final {
public:
  Vector(std::size_t initial_capacity = 4)
      : m_array(new T[initial_capacity]{}), m_size(initial_capacity),
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

  Vector &operator=(const Vector &other) {
    Vector tmp (other);
    swap(tmp);
    return *this;
  }

  Vector &operator=(Vector &&other) {
    swap(other);
    return *this;
  }

  T &operator[](std::size_t idx) &{
    assert(idx < size());
    return *(m_array + idx);
  }

  T &operator[](std::size_t idx) const &{
    assert(idx < size());
    return *(m_array + idx);
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
  using iterator = T*;
  using const_iterator = T*;
  iterator begin() & {return m_array; }
  const_iterator begin() const & {return m_array; }
  iterator end() & {return m_array + m_size; }
  const_iterator end() const & {return m_array + m_size; }

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
} // namespace yacc
