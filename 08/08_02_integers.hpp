#pragma once
#include <cassert>
#include <cctype>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <format>
#include <istream>
#include <limits>
#include <numeric>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace yacc {

class Integer final {
public:
  using DigitT = long long int;

  Integer() : MIsNegative{false}, MDigits(kSize, 0), MSize{1} {}

  Integer(DigitT Digit) : MIsNegative{Digit < 0}, MDigits(kSize, 0), MSize{1} {
    MDigits.front() = Digit;
  }

  Integer(const std::string &Str)
      : Integer{static_cast<std::string_view>(Str)} {}

  /*
   * 12334456789123456789123456789
   * ^                            ^
   * 0                      string.size()
   */
  Integer(std::string_view String)
      : MIsNegative{String.front() == '-'}, MDigits(kSize, 0), MSize{0} {
    for (auto Last = std::ssize(String) - 1; Last >= 0; Last -= kStep) {
      auto Begin = std::max(0l, Last - kStep + 1);

      if (Begin == 0 && !std::isdigit(String.front())) {
        ++Begin;
      }

      if (const auto DigitSv = String.substr(Begin, Last - Begin + 1);
          DigitSv.size() > 0) {
        DigitT Digit;
        const char *End = DigitSv.data() + DigitSv.size();
        const auto [Ptr, Ec] = std::from_chars(DigitSv.data(), End, Digit);
        assert(Ec != std::errc::result_out_of_range);
        if (Ec == std::errc::invalid_argument || Ptr != End) {
          throw std::invalid_argument{"could not parse a number"};
        }
        MDigits[MSize++] = Digit;
      }
    }

    reduce();
  }

  void swap(Integer &Other) noexcept {
    using std::swap;
    swap(MIsNegative, Other.MIsNegative);
    swap(MDigits, Other.MDigits);
    swap(MSize, Other.MSize);
  }

  bool sign() const noexcept { return !MIsNegative; }

  Integer abs() const {
    auto Tmp = *this;
    Tmp.MIsNegative = false;
    return Tmp;
  }

  Integer &operator+=(Integer Other) {
    if (MIsNegative == Other.MIsNegative) {
      this->add(Other);
    } else if (!MIsNegative && Other.MIsNegative) {
      if (this->less(Other)) {
        *this = std::move(Other.subtract(*this));
        MIsNegative = true;
      } else {
        this->subtract(Other);
      }
    } else {
      if (this->less(Other)) {
        *this = std::move(Other.subtract(*this));
      } else {
        this->subtract(Other);
        MIsNegative = true;
      }
    }

    return *this;
  }

  Integer &operator-=(Integer Other) {
    Other.MIsNegative = !Other.MIsNegative;
    return *this += Other;
  }

  Integer &operator*=(Integer Other) {
    Integer X;

    X.MIsNegative = MIsNegative ^ Other.MIsNegative;

    for (auto I = 0uz; I < MSize; ++I) {
      DigitT Remainder = 0;

      for (auto J = 0uz; (J < Other.MSize) || Remainder; ++J) {
        X.MDigits[I + J] += MDigits[I] * Other.MDigits[J] + Remainder;

        Remainder = X.MDigits[I + J] / SBase;

        X.MDigits[I + J] -= Remainder * SBase;
      }
    }

    X.MSize = MSize + Other.MSize;

    swap(X);

    reduce();

    return *this;
  }

  Integer &operator/=(Integer Other) {
    Integer X;

    X.MSize = MSize;

    X.MIsNegative = MIsNegative ^ Other.MIsNegative;

    Other.MIsNegative = false;

    Integer Current;

    for (auto I = static_cast<int>(MSize) - 1; I >= 0; --I) {
      Current *= SBase;

      Current.MDigits.front() = MDigits[I];

      DigitT Left = 0, Right = SBase, Digit = 0;

      while (Left <= Right) {
        if (auto Middle = std::midpoint(Left, Right);
            Other * Middle <= Current) {
          Left = Middle + 1;

          Digit = Middle;
        } else {
          Right = Middle - 1;
        }
      }

      X.MDigits[I] = Digit;

      Current -= Other * Digit;
    }

    swap(X);

    reduce();

    return *this;
  }

  Integer &operator%=(Integer Other) {
    // { x == ((x / a) * a + x % a) } ==> { x % a == x - ((x / a) * a) }
    return *this -= ((*this / Other) * Other);
  }

  Integer &operator++() { return *this += 1; }
  Integer operator++(int) {
    auto X = *this;
    ++(*this);
    return X;
  }

  Integer &operator--() { return *this -= 1; }
  Integer operator--(int) {
    auto X = *this;
    --(*this);
    return X;
  }

  friend Integer operator+(Integer Lhs, const Integer &Rhs) {
    return std::move(Lhs += Rhs);
  }
  friend Integer operator-(Integer Lhs, const Integer &Rhs) {
    return std::move(Lhs -= Rhs);
  }
  friend Integer operator*(Integer Lhs, const Integer &Rhs) {
    return std::move(Lhs *= Rhs);
  }
  friend Integer operator/(Integer Lhs, const Integer &Rhs) {
    return std::move(Lhs /= Rhs);
  }
  friend Integer operator%(Integer Lhs, const Integer &Rhs) {
    return std::move(Lhs %= Rhs);
  }

  friend Integer pow(Integer X, unsigned N) {
    if (X < 2 || N == 1) {
      return X;
    }

    Integer Acc = 1;
    while (N > 0) {
      if ((N & 0x1u) == 0x1u) {
        Acc *= X;
        N -= 1;
      }
      X *= X;
      N /= 2;
    }
    return Acc;
  }

  friend bool operator<(const Integer &Lhs, const Integer &Rhs) {
    if (Lhs.MIsNegative != Rhs.MIsNegative) {
      return Lhs.MIsNegative;
    }

    if (Lhs.MIsNegative && Rhs.MIsNegative) {
      return Rhs.less(Lhs);
    } else {
      return Lhs.less(Rhs);
    }
  }

  friend bool operator>(const Integer &Lhs, const Integer &Rhs) {
    return (Rhs < Lhs);
  }
  friend bool operator<=(const Integer &Lhs, const Integer &Rhs) {
    return !(Rhs < Lhs);
  }
  friend bool operator>=(const Integer &Lhs, const Integer &Rhs) {
    return !(Lhs < Rhs);
  }

  friend bool operator==(const Integer &Lhs, const Integer &Rhs) {
    if (Lhs.MIsNegative != Rhs.MIsNegative || Lhs.MSize != Rhs.MSize) {
      return false;
    }

    for (auto I = 0uz; I < Lhs.MSize; ++I) {
      if (Lhs.MDigits[I] != Rhs.MDigits[I]) {
        return false;
      }
    }

    return true;
  }

  friend std::istream &operator>>(std::istream &Stream, Integer &Int) {
    std::string Str;
    Stream >> Str;
    if (!Stream.bad()) {
      Int = Integer(Str);
    }
    return Stream;
  }

  friend std::ostream &operator<<(std::ostream &Stream,
                                  const Integer &Integer) {
    if (Integer.MIsNegative) {
      Stream << '-';
    }

    Stream << Integer.MDigits[Integer.MSize - 1];

    for (auto I = static_cast<int>(Integer.MSize) - 2; I >= 0; --I) {
      Stream << std::format("{:0>{}}", Integer.MDigits[I], Integer::kStep);
    }

    return Stream;
  }

  friend auto sqrt(const Integer &X) {
    Integer Y;

    Y.MSize = (X.MSize + 1) / 2;

    for (auto I = static_cast<int>(Y.MSize) - 1; I >= 0; --I) {
      DigitT Left = 0, Right = Integer::SBase, Digit = 0;

      while (Left <= Right) {
        auto Middle = Y.MDigits[I] = std::midpoint(Left, Right);

        if (Y * Y <= X) {
          Left = Middle + 1;

          Digit = std::min(Middle, Integer::SBase - 1);
        } else {
          Right = Middle - 1;
        }
      }

      Y.MDigits[I] = Digit;
    }

    Y.reduce();

    return Y;
  }

  friend auto multiply(const Integer &X, const Integer &Y) -> Integer {
    if (auto Size = std::max(X.MSize, Y.MSize); Size > 1) {
      auto Step = Size / 2;

      Integer X1, X2;

      X1.MSize = Step;

      X2.MSize = Size - Step;

      for (auto I = 0uz; I < Step; ++I) {
        X1.MDigits[I] = X.MDigits[I];
      }

      for (auto I = Step; I < Size; ++I) {
        X2.MDigits[I - Step] = X.MDigits[I];
      }

      Integer Y1, Y2;

      Y1.MSize = Step;

      Y2.MSize = Size - Step;

      for (auto I = 0uz; I < Step; ++I) {
        Y1.MDigits[I] = Y.MDigits[I];
      }

      for (auto I = Step; I < Size; ++I) {
        Y2.MDigits[I - Step] = Y.MDigits[I];
      }

      auto A = multiply(X2, Y2);

      auto B = multiply(X1, Y1);

      auto C = multiply(X2 + X1, Y2 + Y1);

      Integer Base = Integer::SBase;

      for (auto I = 1uz; I < Step; ++I) {
        Base *= Integer::SBase;
      }

      auto Z = A * Base * Base + (C - B - A) * Base + B;

      Z.MIsNegative = X.MIsNegative ^ Y.MIsNegative;

      return Z;
    } else {
      return X * Y;
    }
  }

private:
  void reduce() {
    while (MSize > 1 && !MDigits[MSize - 1]) {
      --MSize;
    }
  }

  Integer &add(const Integer &Other) {
    MSize = std::max(MSize, Other.MSize);

    for (auto I = 0uz; I < MSize; ++I) {
      MDigits[I] += Other.MDigits[I];

      if (MDigits[I] >= SBase) {
        MDigits[I] -= SBase;

        MDigits[I + 1]++;
      }
    }

    MSize += MDigits[MSize];

    return *this;
  }

  Integer &subtract(const Integer &Other) {
    for (auto I = 0uz; I < MSize; ++I) {
      MDigits[I] -= Other.MDigits[I];

      if (MDigits[I] < 0) {
        MDigits[I] += SBase;

        MDigits[I + 1]--;
      }
    }

    reduce();

    return *this;
  }

  bool less(const Integer &Other) const {
    if (MSize != Other.MSize) {
      return MSize < Other.MSize;
    }

    for (auto I = static_cast<int>(MSize) - 1; I >= 0; --I) {
      if (MDigits[I] != Other.MDigits[I]) {
        return MDigits[I] < Other.MDigits[I];
      }
    }

    return false;
  }

  static constexpr std::size_t kSize = 1'000uz;
  static constexpr std::ptrdiff_t kStep =
      std::numeric_limits<DigitT>::digits10 / 2;
  static inline const auto SBase = static_cast<DigitT>(std::pow(10, kStep));

  bool MIsNegative;
  std::vector<DigitT> MDigits;
  std::size_t MSize;
};

} // namespace yacc
