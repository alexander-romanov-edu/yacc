#include <limits>

#include <gtest/gtest.h>

#include "08_03_log.hpp"

TEST(Log, Negative) {
  EXPECT_THROW(yacc::log(-1), std::domain_error);
  EXPECT_THROW(yacc::log(-1.0f), std::domain_error);
}

TEST(Log, Zero) {
  EXPECT_THROW(yacc::log(0), std::domain_error);
  EXPECT_THROW(yacc::log(0.0f), std::domain_error);
  EXPECT_THROW(yacc::log(-0.0f), std::domain_error);
}

TEST(Log, ThrowOnNAN) {
  EXPECT_THROW(yacc::log(std::numeric_limits<float>::quiet_NaN()),
               std::domain_error);
  EXPECT_THROW(yacc::log(std::numeric_limits<float>::signaling_NaN()),
               std::domain_error);
}

TEST(Log, ThrowOnInfinity) {
  EXPECT_THROW(yacc::log(std::numeric_limits<float>::infinity()),
               std::domain_error);
  EXPECT_THROW(yacc::log(-std::numeric_limits<float>::infinity()),
               std::domain_error);
}

TEST(Log, VariousInts) {
  EXPECT_EQ(0, yacc::log(1));
  EXPECT_EQ(1, yacc::log(2));
  EXPECT_EQ(1, yacc::log(3));
  EXPECT_EQ(2, yacc::log(4));
  EXPECT_EQ(2, yacc::log(5));
  EXPECT_EQ(2, yacc::log(6));
  EXPECT_EQ(2, yacc::log(7));
  EXPECT_EQ(3, yacc::log(8));
}

TEST(Log, VariousFloats) {
  EXPECT_EQ(0, yacc::log(1.0f));
  EXPECT_EQ(1, yacc::log(2.0f));
  EXPECT_EQ(1, yacc::log(3.0f));
  EXPECT_EQ(2, yacc::log(4.0f));
  EXPECT_EQ(2, yacc::log(5.0f));
  EXPECT_EQ(2, yacc::log(6.0f));
  EXPECT_EQ(2, yacc::log(7.0f));
  EXPECT_EQ(3, yacc::log(8.0f));
}

TEST(Log, IntMaxPositive) {
  EXPECT_EQ(sizeof(int) * CHAR_BIT - 2,
            yacc::log(std::numeric_limits<int>::max()));
}

TEST(Log, Denorm) {
  EXPECT_EQ(-126 - 23, yacc::log(std::numeric_limits<float>::denorm_min()));
}
