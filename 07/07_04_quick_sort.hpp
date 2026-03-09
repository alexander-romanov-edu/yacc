#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>

namespace yacc {

namespace detail {

template <std::random_access_iterator It, typename Compare>
void insertionSort(It First, It Last, Compare Comp) {
  for (auto I = std::next(First); I != Last; ++I) {
    for (auto J = I; J != First; --J) {
      if (auto BeforeJ = std::prev(J); Comp(*J, *BeforeJ)) {
        std::iter_swap(J, BeforeJ);
      }
    }
  }
}

template <std::random_access_iterator It, typename Compare>
It pivot(It First, It Last, Compare Comp) {
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

  auto PivotIt = yacc::detail::pivot(First, Last, Comp);
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

template <std::random_access_iterator It, typename Compare>
void sort(It First, It Last, Compare Comp) {
  if (First >= Last) {
    return;
  }

  constexpr std::ptrdiff_t KQuickSortThreshold = 16;
  if (std::distance(First, Last) >= KQuickSortThreshold) {
    auto Q = yacc::detail::partition(First, Last, Comp);
    yacc::sort(First, Q, Comp);
    yacc::sort(std::next(Q), Last, Comp);
  } else {
    yacc::detail::insertionSort(First, Last, Comp);
  }
}

template <std::random_access_iterator It> void sort(It First, It Last) {
  sort(First, Last, std::less{});
}

} // namespace yacc
