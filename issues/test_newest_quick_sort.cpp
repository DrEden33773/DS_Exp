/**
 * @file test_newest_quick_sort.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief test_newest_quick_sort
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

// success

#include <algorithm>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

namespace ranges = std::ranges;

template <class I, std::sentinel_for<I> S, class Cmp = ranges::less>
requires std::sortable<I, Cmp>
void quicksort(I first, S last, Cmp cmp = Cmp {}) {
    using reference = std::iter_reference_t<I>;

    if (first == last) {
        return;
    }

    auto size  = ranges::distance(first, last);
    auto pivot = ranges::next(first, size - 1);
    ranges::iter_swap(pivot, ranges::next(first, size / 2));

    auto tail = ranges::partition(first, pivot, [=](reference em) {
        // em < pivot
        return std::invoke(cmp, em, *pivot);
    });

    ranges::iter_swap(pivot, tail.begin());
    quicksort(first, tail.begin(), std::ref(cmp));
    quicksort(ranges::next(tail.begin()), last, std::ref(cmp));
}

int main() {
    std::ostream_iterator<int> cout { std::cout, " " };

    std::vector<int> v { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << "Original vector:  \t";
    ranges::copy(v, cout);

    auto tail = ranges::partition(v, [](int i) { return i % 2 == 0; });

    std::cout << "\nPartitioned vector: \t";
    ranges::copy(ranges::begin(v), ranges::begin(tail), cout);
    std::cout << "│ ";
    ranges::copy(tail, cout);

    std::forward_list<int> fl { 1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92 };
    std::cout << "\nUnsorted list: \t\t";
    ranges::copy(fl, cout);

    quicksort(ranges::begin(fl), ranges::end(fl), ranges::greater {});
    std::cout << "\nQuick-sorted list: \t";
    ranges::copy(fl, cout);

    std::cout << '\n';
}