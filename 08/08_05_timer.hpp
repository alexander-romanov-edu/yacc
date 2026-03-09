#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>

namespace yacc {

class Timer {
  using D = std::chrono::duration<double>;
  using clock_t = std::chrono::steady_clock;

public:
  Timer() = default;

  void start() {
    if (!m_running) {
      m_running = true;
      m_begin = clock_t::now();
    }
  }

  void stop() {
    if (m_running) {
      m_running = false;
      m_intervals.emplace_back(
          std::chrono::duration_cast<D>(clock_t::now() - m_begin));
    }
  }

  std::optional<D> average() const {
    return std::ranges::fold_left_first(m_intervals, std::plus{})
        .transform([count = m_intervals.size()](D sum) { return sum / count; });
  }

private:
  bool m_running = false;
  clock_t::time_point m_begin;
  std::vector<D> m_intervals;
};

} // namespace yacc
