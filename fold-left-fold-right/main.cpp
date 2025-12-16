#include <iostream>
#include <vector>
#include <numeric>    // accumulate, fold_*
#include <functional> // std::plus
#include <optional>

template <typename Range, typename T, typename Op>
T
fold_left(const Range& r, T init, Op op)
{
    for (auto&& v : r)
        init = op(init, v);
    return init;
}

template <typename Range, typename T, typename Op>
T
fold_right(const Range& r, T init, Op op)
{
    for (auto it = r.rbegin(); it != r.rend(); ++it)
        init = op(*it, init);
    return init;
}

// fold_left_first: uses the first element of the range as the initial value
template <typename Range, typename Op>
std::optional<typename Range::value_type>
fold_left_first(const Range& r, Op op)
{
    auto it = r.begin();
    if (it == r.end())
        return std::nullopt;
    auto init = *it++;
    for (; it != r.end(); ++it)
        init = op(init, *it);
    return init;
}

// fold_right_first: uses the first element of the range as the initial value
template <typename Range, typename Op>
std::optional<typename Range::value_type>
fold_right_first(const Range& r, Op op)
{
    auto it = r.rbegin();
    if (it == r.rend())
        return std::nullopt;
    auto init = *it++;
    for (; it != r.rend(); ++it)
        init = op(*it, init);
    return init;
}

int
main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Fold left (classic)
    int sum_left = std::accumulate(numbers.begin(), numbers.end(), 0, std::plus<int>{});
    std::cout << "Fold left (sum): " << sum_left << '\n';

    // Fold right (classic using reverse iterators)
    int sum_right = std::accumulate(numbers.rbegin(), numbers.rend(), 0, std::plus<int>{});
    std::cout << "Fold right (sum): " << sum_right << '\n';

    // Fold left with ranges (C++23)
    int sum_ranges = fold_left(numbers, 0, std::plus{});
    std::cout << "Fold left with ranges (sum): " << sum_ranges << '\n';

    // Fold right with ranges (C++23)
    int sum_ranges_right = fold_right(numbers, 0, std::plus{});
    std::cout << "Fold right with ranges (sum): " << sum_ranges_right << '\n';

    // Fold left using first element as initial value
    if (auto sum_first = fold_left_first(numbers, std::plus{})) {
        std::cout << "Fold left first element (sum): " << *sum_first << '\n';
    }

    // Fold right using first element as initial value
    if (auto sum_right_first = fold_right_first(numbers, std::plus{})) {
        std::cout << "Fold right first element (sum): " << *sum_right_first << '\n';
    }

    return 0;
}
