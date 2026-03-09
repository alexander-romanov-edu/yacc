
#include <climits>
#include <cstdint>
#include <stdexcept>

static_assert(sizeof(int) == sizeof(float));

namespace yacc {

static_assert(std::endian::native == std::endian::little);

template <std::integral T> constexpr std::size_t kNBits = sizeof(T) * CHAR_BIT;

template <std::size_t n, std::unsigned_integral T>
  requires(n < kNBits<T>)
constexpr T mask_bit(T num) noexcept {
  return num & (T{1} << n);
}

template <std::size_t to, std::size_t from, std::unsigned_integral T>
  requires(from < to && to < kNBits<T>)
constexpr T get_mask() noexcept {
  using U =
      std::conditional_t<(kNBits<T> < kNBits<std::uint32_t>), std::uint32_t, T>;
  return (~U{0} >> (kNBits<U> - to - 1)) - ((U{1} << from) - U{1});
}

template <std::size_t to, std::size_t from, std::unsigned_integral T>
  requires(from < to && to < kNBits<T>)
constexpr T get_bits(T num) noexcept {
  return (num & get_mask<to, from, T>()) >> from;
}

constexpr int log(int x) {
  if (x <= 0) {
    throw std::domain_error{"log(x) is not defined for x <= 0"};
  }

  auto ux = static_cast<unsigned>(x);

  int i = 0;
  for (; ux >>= 1; ++i) {
    // just iterate
  }

  return i;
}

inline int log(float x) {
  if (x <= 0) {
    throw std::domain_error{"log(x) is not defined for x <= 0"};
  }

  union {
    float fp;
    unsigned integer;
  } num{x};

  unsigned exp = get_bits<30, 23>(num.integer);

  if (exp == 0xffu) { // NAN
    throw std::domain_error{"log(NAN/+inf/-inf) is not defined"};
  }

  if (exp != 0u) { // normalized number: 1.fraction * 2^(exp - 127)
    return static_cast<int>(exp) - 127;
  }

  // denormalized numbers: 0.fraction * 2^(-126)
  unsigned mantissa = get_bits<22, 0>(num.integer);
  int actual_exp = -126;
  while (mask_bit<22>(mantissa) == 0) {
    mantissa <<= 1;
    --actual_exp;
  }

  return actual_exp - 1; // because of 0.fraction instead of 1.fraction
}

} // namespace yacc
