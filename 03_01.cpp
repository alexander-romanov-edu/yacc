#include <algorithm>
#include <concepts>
#include <optional>
#include <print>
#include <vector>

template <std::integral side_type> struct Rectangle {
  side_type left;
  side_type top;
  side_type right;
  side_type bottom;

  side_type area() const { return (right - left) * (bottom - top); }

  std::optional<Rectangle> intersect(const Rectangle &other) const {
    Rectangle r{std::max(left, other.left), std::max(top, other.top),
                std::min(right, other.right), std::min(bottom, other.bottom)};
    if (r.left >= r.right || r.top >= r.bottom)
      return std::nullopt;
    return r;
  }

  void extend_to_include(const Rectangle &other) {
    left = std::min(left, other.left);
    top = std::min(top, other.top);
    right = std::max(right, other.right);
    bottom = std::max(bottom, other.bottom);
  }
};

template <typename T>
std::optional<Rectangle<T>> intersect_all(const std::vector<Rectangle<T>> &v) {
  if (v.empty())
    return std::nullopt;

  auto r = v.front();
  for (size_t i = 1; i < v.size(); ++i) {
    auto tmp = r.intersect(v[i]);
    if (!tmp)
      return std::nullopt;
    r = *tmp;
  }
  return r;
}

template <typename T>
std::optional<Rectangle<T>> bounding(const std::vector<Rectangle<T>> &v) {
  if (v.empty())
    return std::nullopt;

  auto r = v.front();
  for (size_t i = 1; i < v.size(); ++i) {
    r.extend_to_include(v[i]);
  }
  return r;
}
int main() {
  std::vector<Rectangle<int>> v{{0, 0, 10, 10}, {5, 5, 15, 15}, {3, 3, 12, 8}};

  if (auto r = intersect_all(v)) {
    std::println("Intersection area = {}", r->area());
  } else {
    std::println("No intersection");
  }

  if (auto b = bounding(v)) {
    std::println("Bounding rectangle: {} {} {} {}", b->left, b->top, b->right,
                 b->bottom);
  }
}
