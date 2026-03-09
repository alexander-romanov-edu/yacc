#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
namespace yacc {

namespace detail {

template <std::random_access_iterator Iter, typename Compare>
void insertionSort(Iter First, Iter Last, Compare Comp) {
  for (auto I = std::next(First); I != Last; ++I) {
    for (auto J = I; J != First; --J) {
      if (auto BeforeJ = std::prev(J); Comp(*J, *BeforeJ)) {
        std::iter_swap(J, BeforeJ);
      }
    }
  }
}

template <std::random_access_iterator Iter, typename Compare>
Iter pivot(Iter First, Iter Last, Compare Comp) {
  assert(First != Last);

  auto MidIt = std::next(First, std::distance(First, Last) / 2);
  --Last;

  if (Comp(*MidIt, *First)) {
    std::iter_swap(MidIt, First);
  }
  if (Comp(*Last, *First)) {
    std::iter_swap(Last, First);
  }
  if (Comp(*MidIt, *Last)) {
    std::iter_swap(MidIt, Last);
  }

  return Last;
}

template <std::random_access_iterator Iter, typename Compare>
Iter partition(Iter First, Iter Last, Compare Comp) {
  assert(First != Last);

  auto PivotIt = detail::pivot(First, Last, Comp);
  --Last;
  auto I = First;
  for (auto It = First; It != Last; ++It) {
    if (!Comp(*PivotIt, *It)) {
      std::iter_swap(I, It);
      ++I;
    }
  }
  std::iter_swap(I, Last);
  return I;
}

} // namespace detail

template <std::random_access_iterator Iter, typename Compare>
void sort(Iter First, Iter Last, std::size_t Threshold, Compare Comp) {
  if (First >= Last) {
    return;
  }

  if (std::distance(First, Last) >=
      static_cast<std::iter_difference_t<Iter>>(Threshold)) {
    auto Q = detail::partition(First, Last, Comp);
    sort(First, Q, Threshold, Comp);
    sort(std::next(Q), Last, Threshold, Comp);
  } else {
    detail::insertionSort(First, Last, Comp);
  }
}

template <std::random_access_iterator Iter>
void sort(Iter First, Iter Last, std::size_t Threshold) {
  sort(First, Last, Threshold, std::less{});
}

} // namespace yacc
