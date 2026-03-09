#pragma once

#include <compare>
#include <concepts>
#include <istream>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <type_traits>

namespace dts {
namespace detail {

template <typename T> struct empty_base {};

} // namespace detail

template <typename T, typename B = detail::empty_base<T>> struct addable : B {
  constexpr friend T operator+(const T &lhs, const T &rhs) {
    return auto(lhs) += rhs;
  }
};

template <typename T, typename B = detail::empty_base<T>>
struct subtractable : B {
  constexpr friend T operator-(const T &lhs, const T &rhs) {
    return auto(lhs) -= rhs;
  }
};

template <typename T, typename B = detail::empty_base<T>>
struct multipliable : B {
  constexpr friend T operator*(const T &lhs, const T &rhs) {
    return auto(lhs) *= rhs;
  }
};

template <typename T, typename B = detail::empty_base<T>> struct dividable : B {
  constexpr friend T operator/(const T &lhs, const T &rhs) {
    return auto(lhs) /= rhs;
  }
};

template <typename T, typename B = detail::empty_base<T>>
struct incrementable : B {
  constexpr friend T operator++(T &val, int) {
    auto copy(val);
    ++val;
    return copy;
  }
};

template <typename T, typename B = detail::empty_base<T>>
struct decrementable : B {
  constexpr friend T operator--(T &val, int) {
    auto copy(val);
    --val;
    return copy;
  }
};

template <typename T>
  requires std::signed_integral<T> && (!std::same_as<std::remove_cv_t<T>, bool>)
class RationalWithMixins final
    // clang-format off
    : private addable<RationalWithMixins<T>,
              subtractable<RationalWithMixins<T>,
              multipliable<RationalWithMixins<T>,
              dividable<RationalWithMixins<T>,
              incrementable<RationalWithMixins<T>,
              decrementable<RationalWithMixins<T>>>>>>> {
  // clang-format on
public:
  constexpr RationalWithMixins(T num = 0, T den = 1) : num_(num), den_(den) {
    if (den == 0) {
      throw std::invalid_argument{"denominator shall not be zero"};
    }
    reduce();
  }

  constexpr T numerator() const noexcept { return num_; }
  constexpr T denominator() const noexcept { return den_; }

  constexpr explicit operator double() const {
    return static_cast<double>(num_) / den_;
  }

  constexpr RationalWithMixins &operator+=(const RationalWithMixins &rhs) {
    const auto lcm = std::lcm(den_, rhs.den_);
    num_ = num_ * (lcm / den_) + rhs.num_ * (lcm / rhs.den_);
    den_ = lcm;

    reduce();

    return *this;
  }

  constexpr RationalWithMixins &operator-=(const RationalWithMixins &other) {
    return *this += RationalWithMixins(-other.num_, other.den_);
  }

  constexpr RationalWithMixins &operator*=(const RationalWithMixins &rhs) {
    num_ *= rhs.num_;
    den_ *= rhs.den_;

    reduce();

    return *this;
  }

  constexpr RationalWithMixins &operator/=(const RationalWithMixins &other) {
    return *this *= RationalWithMixins(other.den_, other.num_);
  }

  constexpr RationalWithMixins &operator++() { return *this += 1; }
  constexpr RationalWithMixins &operator--() { return *this -= 1; }

  constexpr friend bool operator==(const RationalWithMixins &lhs,
                                   const RationalWithMixins &rhs) {
    return lhs.num_ == rhs.num_ && lhs.den_ == rhs.den_;
  }

  constexpr friend std::strong_ordering
  operator<=>(const RationalWithMixins &lhs, const RationalWithMixins &rhs) {
    return lhs.num_ * rhs.den_ <=> rhs.num_ * lhs.den_;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const RationalWithMixins &rational) {
    return os << rational.num_ << '/' << rational.den_;
  }

  friend std::istream &operator>>(std::istream &is,
                                  RationalWithMixins &rational) {
    is >> rational.num_;

    char c{};
    is >> c;
    if (c != '/') {
      is.setstate(std::ios_base::failbit);
    }

    T den = 1; // intentionally non-zero value
    is >> den;
    if (den == 0) {
      throw std::invalid_argument{"denominator shall not be zero"};
    }
    rational.den_ = den;

    rational.reduce();

    return is;
  }

private:
  constexpr void reduce() {
    if (den_ < 0) {
      num_ = -num_;
      den_ = -den_;
    }

    const auto gcd = std::gcd(num_, den_);
    num_ /= gcd;
    den_ /= gcd;
  }

  T num_;
  T den_;
};
} // namespace dts
