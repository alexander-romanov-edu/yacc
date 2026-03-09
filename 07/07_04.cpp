#include <deque>
#include <format>

#include <gtest/gtest.h>

#include "07_04_quick_sort.hpp"

TEST(QuickSort, EmptySequence) {
  // Assign
  std::deque<int> d;

  // Act
  yacc::sort(d.begin(), d.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, OneElement) {
  // Assign
  std::deque<int> d{42};

  // Act
  yacc::sort(d.begin(), d.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, TwoElementsSorted) {
  // Assign
  std::deque<int> d{1, 2};

  // Act
  yacc::sort(d.begin(), d.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, TwoElementsNotSorted) {
  // Assign
  std::deque<int> d{2, 1};

  // Act
  yacc::sort(d.begin(), d.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, TwoElementsEqual) {
  // Assign
  std::deque<int> d{1, 1};

  // Act
  yacc::sort(d.begin(), d.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, UnsortedSequenceLessThanThreshold) {
  // Assign
  std::deque<int> d{-5, 1, 12, 2, 8, 9, 5, 8, 11, -12, 37, 42, 1, 35};

  // Act
  yacc::sort(d.begin(), d.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, UnsortedSequenceLessThanThresholdWithOtherComparator) {
  // Assign
  std::deque<int> d{-5, 1, 12, 2, 8, 9, 5, 8, 11, -12, 37, 42, 1, 35};
  std::greater cmp;

  // Act
  yacc::sort(d.begin(), d.end(), cmp);

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d, cmp)) << std::format("{}", d);
}

TEST(QuickSort, UnsortedSequence) {
  // Assign
  std::deque<int> d{-5, 1,  12,  2,   8,  9,  5,   8, 11, -12, 37,  42,
                    1,  35, 104, 213, 25, 84, -72, 0, 29, 31,  1058};

  // Act
  yacc::sort(d.begin(), d.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, UnsortedSequenceWithOtherComparator) {
  // Assign
  std::deque<int> d{-5, 1,  12,  2,   8,  9,  5,   8, 11, -12, 37,  42,
                    1,  35, 104, 213, 25, 84, -72, 0, 29, 31,  1058};
  std::greater cmp;

  // Act
  yacc::sort(d.begin(), d.end(), cmp);

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(d, cmp)) << std::format("{}", d);
}

TEST(QuickSort, Strings) {
  // Assign
  std::deque<std::string> strings{
      "lorem",       "ipsum",      "dolor",      "sit",   "amet",
      "consectetur", "adipiscing", "elit",       "sed",   "do",
      "eiusmod",     "tempor",     "incididunt", "ut",    "labore",
      "et",          "dolore",     "magna",      "aliqua"};

  // Act
  yacc::sort(strings.begin(), strings.end());

  // Assert
  EXPECT_TRUE(std::ranges::is_sorted(strings)) << std::format("{}", strings);
}
