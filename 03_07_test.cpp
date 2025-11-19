#include "03_07.hpp"

#include <gtest/gtest.h>

using namespace yacc;
TEST(VectorTest, DefCtor) {
  Vector<int> v;
  ASSERT_EQ(v.size(), 4u);
  Vector<int> v2(1);
  ASSERT_EQ(v2.size(), 1u);
  for (auto e: v2)
    EXPECT_EQ(e, 0);
}

TEST(VectorTest, CtorInitList) {
  Vector<int> v {0, 1, 1, 4,-1};
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 1);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], -1);
}

TEST(VectorTest, CtorCopy) {
  Vector<int> v1 {0, 1, 1, 4,-1};
  Vector<int> v2 = v1;
  ASSERT_EQ(v2.size(), 5u);
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 1);
  EXPECT_EQ(v2[2], 1);
  EXPECT_EQ(v2[3], 4);
  EXPECT_EQ(v2[4], -1);
}

TEST(VectorTest, CtorMove) {
  Vector<int> v1 {0, 1, 1, 4,-1};
  Vector<int> v2 = std::move(v1);
  ASSERT_EQ(v2.size(), 5u);
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 1);
  EXPECT_EQ(v2[2], 1);
  EXPECT_EQ(v2[3], 4);
  EXPECT_EQ(v2[4], -1);
}

TEST(VectorTest, Swap) {
  Vector<int> v1 {0, 1, 1, 4,-1};
  Vector<int> v2 = {3,4 ,2};
  v1.swap(v2);
  ASSERT_EQ(v2.size(), 5u);
  ASSERT_EQ(v1.size(), 3u);

  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 1);
  EXPECT_EQ(v2[2], 1);
  EXPECT_EQ(v2[3], 4);
  EXPECT_EQ(v2[4], -1);

  EXPECT_EQ(v1[0], 3);
  EXPECT_EQ(v1[1], 4);
  EXPECT_EQ(v1[2], 2);
}
