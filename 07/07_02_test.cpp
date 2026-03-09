#include <gtest/gtest.h>

#include "07_02_operators.hpp"

template <typename T>
class RationalWithExceptionsTest : public ::testing::Test {};

using IntegralTypes = ::testing::Types<short, int, long, long long>;

TYPED_TEST_SUITE(RationalWithExceptionsTest, IntegralTypes);

TYPED_TEST(RationalWithExceptionsTest, ZeroDenominatorInCtor) {
  EXPECT_THROW(dts::RationalWithExceptions<TypeParam>(1, 0), dts::Exception);
}

TYPED_TEST(RationalWithExceptionsTest, ZeroDenominatorInDeserialization) {
  // Assign
  std::stringstream ss;
  ss << "1/0";
  dts::RationalWithExceptions<TypeParam> r;

  // Act & Assert
  EXPECT_THROW(ss >> r, dts::Exception);
}
