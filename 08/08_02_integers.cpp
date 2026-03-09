#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "08_02_integers.hpp"

using namespace std::string_view_literals;

TEST(Integer, Sign) {
  // Assign
  const yacc::Integer zero = "0"sv;
  const yacc::Integer x = "123"sv;
  const yacc::Integer y = "-123"sv;

  // Act & Assert
  EXPECT_TRUE(zero.sign());
  EXPECT_TRUE(x.sign());
  EXPECT_FALSE(y.sign());
}

TEST(Integer, Abs) {
  // Assign
  const yacc::Integer zero = "0"sv;
  const yacc::Integer x = "123"sv;
  const yacc::Integer y = "-123"sv;

  // Act & Assert
  EXPECT_EQ(zero.abs(), zero);
  EXPECT_EQ(x.abs(), x);
  EXPECT_EQ(y.abs(), "123"sv);
}

TEST(Integer, PlusEqual) {
  // Assign
  yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act
  x += y;

  // Assert
  EXPECT_EQ(x, "+33333333333333333333333333333333"sv);
}

TEST(Integer, MinusEqual) {
  // Assign
  yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act
  x -= y;

  // Assert
  EXPECT_EQ(x, "-11111111111111111111111111111111"sv);
}

TEST(Integer, MulEqual) {
  // Assign
  yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act
  x *= y;

  // Assert
  EXPECT_EQ(
      x, "+246913580246913580246913580246908641975308641975308641975308642"sv);
}

TEST(Integer, DivEqual) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  yacc::Integer y = std::string(32, '2');

  // Act
  y /= x;

  // Assert
  EXPECT_EQ(y, "+2"sv);
}

TEST(Integer, RemainderEqual) {
  // Assign
  yacc::Integer x = "1358023802380480882350720497150012330"sv;
  const yacc::Integer y = "17"sv;

  // Act
  x %= y;

  // Assert
  EXPECT_EQ(x, "+8"sv);
}

TEST(Integer, Plus) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act
  const auto sum = x + y;

  // Assert
  EXPECT_EQ(sum, "+33333333333333333333333333333333"sv);
}

TEST(Integer, Minus) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act
  const auto diff = x - y;

  // Assert
  EXPECT_EQ(diff, "-11111111111111111111111111111111"sv);
}

TEST(Integer, Mul) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act
  const auto prod = x * y;

  // Assert
  EXPECT_EQ(
      prod,
      "+246913580246913580246913580246908641975308641975308641975308642"sv);
}

TEST(Integer, Div) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act
  const auto quot = y / x;

  // Assert
  EXPECT_EQ(quot, "+2"sv);
}

TEST(Integer, Remainder) {
  // Assign
  const yacc::Integer x = "1358023802380480882350720497150012330"sv;
  const yacc::Integer y = "17"sv;

  // Act
  const auto rem = x % y;

  // Assert
  EXPECT_EQ(rem, "+8"sv);
}

TEST(Integer, Pow) {
  // Assign
  const yacc::Integer x = "89789780958108235"sv;

  // Act
  const auto rem = pow(x, 5);

  // Assert
  EXPECT_EQ(
      rem,
      "5836259051707283356505718574890111231432492302826366037603116628036461926442790646875"sv);
}

TEST(Integer, PreIncrement) {
  // Assign
  yacc::Integer x = std::string(32, '1');

  // Act
  const auto res = ++x;

  // Assert
  EXPECT_EQ(x, "+11111111111111111111111111111112"sv);
  EXPECT_EQ(res, "+11111111111111111111111111111112"sv);
}

TEST(Integer, PostIncrement) {
  // Assign
  yacc::Integer x = std::string(32, '1');

  // Act
  const auto res = x++;

  // Assert
  EXPECT_EQ(x, "+11111111111111111111111111111112"sv);
  EXPECT_EQ(res, "+11111111111111111111111111111111"sv);
}

TEST(Integer, PreDecrement) {
  // Assign
  yacc::Integer x = std::string(32, '1');

  // Act
  const auto res = --x;

  // Assert
  EXPECT_EQ(x, "+11111111111111111111111111111110"sv);
  EXPECT_EQ(res, "+11111111111111111111111111111110"sv);
}

TEST(Integer, PostDecrement) {
  // Assign
  yacc::Integer x = std::string(32, '1');

  // Act
  const auto res = x--;

  // Assert
  EXPECT_EQ(x, "+11111111111111111111111111111110"sv);
  EXPECT_EQ(res, "+11111111111111111111111111111111"sv);
}

TEST(Integer, Less) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act & Assert
  EXPECT_TRUE(x < y);
}

TEST(Integer, LessEqual) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act & Assert
  EXPECT_TRUE(x <= y);
}

TEST(Integer, Greater) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act & Assert
  EXPECT_FALSE(x > y);
}

TEST(Integer, GreaterEqual) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act & Assert
  EXPECT_FALSE(x >= y);
}

TEST(Integer, Equal) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act & Assert
  EXPECT_FALSE(x == y);
}

TEST(Integer, NotEqual) {
  // Assign
  const yacc::Integer x = std::string(32, '1');
  const yacc::Integer y = std::string(32, '2');

  // Act & Assert
  EXPECT_TRUE(x != y);
}

TEST(Integer, Deserialization) {
  // Assign
  const std::string str(32, '1');
  yacc::Integer x;
  std::stringstream stream_1;

  // Act
  stream_1 << str;
  stream_1 >> x;

  // Assert
  EXPECT_EQ(x, str);
}

TEST(Integer, Serialization) {
  // Assign
  const std::string x_str(32, '1');
  const yacc::Integer x{x_str};
  std::string y_str;
  std::stringstream stream;

  // Act
  stream << x;
  stream >> y_str;

  // Assert
  EXPECT_EQ(x_str, y_str);
}
