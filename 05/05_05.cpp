#include <gtest/gtest.h>

#include "05_05.hpp"

template <typename T> class RationalWithMixinTest : public ::testing::Test {};

using IntegralTypes = ::testing::Types<short, int, long, long long>;

TYPED_TEST_SUITE(RationalWithMixinTest, IntegralTypes);

TYPED_TEST(RationalWithMixinTest, PlusEqual) {
  // Assign
  yacc::RationalWithMixins<TypeParam> lhs{5, 2};
  const yacc::RationalWithMixins<TypeParam> rhs{7, 6};

  // Act
  lhs += rhs;

  // Assert
  EXPECT_EQ(lhs.numerator(), 11);
  EXPECT_EQ(lhs.denominator(), 3);
  EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 11.0 / 3.0);
}

TYPED_TEST(RationalWithMixinTest, Plus) {
  // Assign
  const yacc::RationalWithMixins<TypeParam> lhs{5, 2};
  const yacc::RationalWithMixins<TypeParam> rhs{7, 6};

  // Act
  const auto sum = lhs + rhs;

  // Assert
  EXPECT_EQ(sum.numerator(), 11);
  EXPECT_EQ(sum.denominator(), 3);
  EXPECT_DOUBLE_EQ(static_cast<double>(sum), 11.0 / 3.0);
}

TYPED_TEST(RationalWithMixinTest, PreIncrement) {
  // Assign
  yacc::RationalWithMixins<TypeParam> r{5, 2};

  // Act
  ++r;

  // Assert
  EXPECT_EQ(r.numerator(), 7);
  EXPECT_EQ(r.denominator(), 2);
  EXPECT_DOUBLE_EQ(static_cast<double>(r), 3.5);
}

TYPED_TEST(RationalWithMixinTest, PostIncrement) {
  // Assign
  yacc::RationalWithMixins<TypeParam> r{5, 2};

  // Act
  const auto old = r++;

  // Assert
  EXPECT_EQ(old.numerator(), 5);
  EXPECT_EQ(old.denominator(), 2);
  EXPECT_DOUBLE_EQ(static_cast<double>(old), 2.5);

  EXPECT_EQ(r.numerator(), 7);
  EXPECT_EQ(r.denominator(), 2);
  EXPECT_DOUBLE_EQ(static_cast<double>(r), 3.5);
}

TYPED_TEST(RationalWithMixinTest, MinusEqual) {
  // Assign
  yacc::RationalWithMixins<TypeParam> lhs{5, 2};
  const yacc::RationalWithMixins<TypeParam> rhs{7, 6};

  // Act
  lhs -= rhs;

  // Assert
  EXPECT_EQ(lhs.numerator(), 4);
  EXPECT_EQ(lhs.denominator(), 3);
  EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 4.0 / 3.0);
}

TYPED_TEST(RationalWithMixinTest, Minus) {
  // Assign
  const yacc::RationalWithMixins<TypeParam> lhs{5, 2};
  const yacc::RationalWithMixins<TypeParam> rhs{7, 6};

  // Act
  const auto sum = lhs - rhs;

  // Assert
  EXPECT_EQ(sum.numerator(), 4);
  EXPECT_EQ(sum.denominator(), 3);
  EXPECT_DOUBLE_EQ(static_cast<double>(sum), 4.0 / 3.0);
}

TYPED_TEST(RationalWithMixinTest, PreDecrement) {
  // Assign
  yacc::RationalWithMixins<TypeParam> r{5, 2};

  // Act
  --r;

  // Assert
  EXPECT_EQ(r.numerator(), 3);
  EXPECT_EQ(r.denominator(), 2);
  EXPECT_DOUBLE_EQ(static_cast<double>(r), 1.5);
}

TYPED_TEST(RationalWithMixinTest, PostDecrement) {
  // Assign
  yacc::RationalWithMixins<TypeParam> r{5, 2};

  // Act
  const auto old = r--;

  // Assert
  EXPECT_EQ(old.numerator(), 5);
  EXPECT_EQ(old.denominator(), 2);
  EXPECT_DOUBLE_EQ(static_cast<double>(old), 2.5);

  EXPECT_EQ(r.numerator(), 3);
  EXPECT_EQ(r.denominator(), 2);
  EXPECT_DOUBLE_EQ(static_cast<double>(r), 1.5);
}

TYPED_TEST(RationalWithMixinTest, MultiplyEqual) {
  // Assign
  yacc::RationalWithMixins<TypeParam> lhs{2, 3};
  const yacc::RationalWithMixins<TypeParam> rhs{3, 2};

  // Act
  lhs *= rhs;

  // Assert
  EXPECT_EQ(lhs.numerator(), 1);
  EXPECT_EQ(lhs.denominator(), 1);
  EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 1.0);
}

TYPED_TEST(RationalWithMixinTest, Multiply) {
  // Assign
  const yacc::RationalWithMixins<TypeParam> lhs{2, 3};
  const yacc::RationalWithMixins<TypeParam> rhs{3, 2};

  // Act
  const auto prod = lhs * rhs;

  // Assert
  EXPECT_EQ(prod.numerator(), 1);
  EXPECT_EQ(prod.denominator(), 1);
  EXPECT_DOUBLE_EQ(static_cast<double>(prod), 1.0);
}

TYPED_TEST(RationalWithMixinTest, DivideEqual) {
  // Assign
  yacc::RationalWithMixins<TypeParam> lhs{5, 2};
  const yacc::RationalWithMixins<TypeParam> rhs{3, 4};

  // Act
  lhs /= rhs;

  // Assert
  EXPECT_EQ(lhs.numerator(), 10);
  EXPECT_EQ(lhs.denominator(), 3);
  EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 10.0 / 3.0);
}

TYPED_TEST(RationalWithMixinTest, Divide) {
  // Assign
  const yacc::RationalWithMixins<TypeParam> lhs{5, 2};
  const yacc::RationalWithMixins<TypeParam> rhs{3, 4};

  // Act
  const auto quot = lhs / rhs;

  // Assert
  EXPECT_EQ(quot.numerator(), 10);
  EXPECT_EQ(quot.denominator(), 3);
  EXPECT_DOUBLE_EQ(static_cast<double>(quot), 10.0 / 3.0);
}
