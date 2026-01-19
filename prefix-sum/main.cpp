/**
Different ways to compute the prefix sum of a list of numbers.
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <stdexcept>

using std::vector;

vector<int>
compute_prefix_sum1(const vector<int>& nums)
{
    if (nums.empty()) {
        return {};
    }
    vector<int> prefix_sum(nums.size());
    prefix_sum[0] = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + nums[i];
    }
    return prefix_sum;
}

vector<int>
compute_prefix_sum2(const vector<int>& nums)
{
    if (nums.empty()) {
        return {};
    }
    vector<int> prefix_sum(nums.size());
    inclusive_scan(nums.begin(), nums.end(), prefix_sum.begin(), std::plus<int>());
    return prefix_sum;
}

vector<int>
compute_prefix_sum3(const vector<int>& nums)
{
    if (nums.empty()) {
        return {};
    }
    vector<int> prefix_sum(nums.size());
    partial_sum(nums.begin(), nums.end(), prefix_sum.begin());
    return prefix_sum;
}

vector<int>
compute_prefix_sum4(const vector<int>& nums)
{
    if (nums.empty()) {
        return {};
    }

    vector<int> prefix_sum;
    prefix_sum.reserve(nums.size());
    int sum = 0;
    for (const auto& num : nums) {
        sum += num;
        prefix_sum.push_back(sum);
    }
    return prefix_sum;
}

vector<int>
compute_prefix_sum5(const vector<int>& nums)
{
    if (nums.empty()) {
        return {};
    }

    vector<int> prefix_sum(nums.size());
    std::transform(
        std::begin(nums), std::end(nums), std::begin(prefix_sum), [n = 0](int num) mutable { return n += num; });
    return prefix_sum;
}

vector<int>
compute_prefix_sum6(const vector<int>& nums)
{
    if (nums.empty()) {
        return {};
    }

    vector<int> prefix_sum;
    prefix_sum.reserve(nums.size());
    std::accumulate(nums.begin(), nums.end(), 0, [&prefix_sum](int acc, int num) {
        int new_sum = acc + num;
        prefix_sum.push_back(new_sum);
        return new_sum;
    });
    return prefix_sum;
}

vector<int>
compute_prefix_sum7(const vector<int>& nums)
{
    if (nums.empty()) {
        return {};
    }

    vector<int> prefix_sum;
    prefix_sum.reserve(nums.size());
    int sum = 0;
    std::for_each(nums.begin(), nums.end(), [&prefix_sum, &sum](int num) {
        sum += num;
        prefix_sum.push_back(sum);
    });
    return prefix_sum;
}

vector<int>
assert_equal(const vector<int>& a, const vector<int>& b)
{
    if (a.size() != b.size()) {
        throw std::runtime_error("Vectors have different sizes");
    }
    if (std::equal(a.begin(), a.end(), b.begin())) {
        return a;
    }
    // if (std::any_of(a.begin(), a.end(), [&, i = 0](int val) mutable {
    //         return val != b[i++];
    //     })) {
    //         throw std::runtime_error("Vectors differ");
    // }
    // if (std::all_of(a.begin(), a.end(), [&, i = 0](int val) mutable {
    //         return val == b[i++];
    //     })) {
    //     return a;
    // }
    throw std::runtime_error("Vectors differ");
}

int
main()
{
    vector<int> nums = {1, 2, 3, 4, 5};
    vector<int> prefix_sum_expected = {1, 3, 6, 10, 15};

    // Method 1: simple loop implementation
    auto prefix_sum1 = compute_prefix_sum1(nums);
    assert_equal(prefix_sum1, prefix_sum_expected);

    // Method 2: using inclusive_scan
    auto prefix_sum2 = compute_prefix_sum2(nums);
    assert_equal(prefix_sum2, prefix_sum_expected);

    // Method 3: using partial_sum
    auto prefix_sum3 = compute_prefix_sum3(nums);
    assert_equal(prefix_sum3, prefix_sum_expected);

    // Method 4: using push_back in a loop
    auto prefix_sum4 = compute_prefix_sum4(nums);
    assert_equal(prefix_sum4, prefix_sum_expected);

    // Method 5: using transform with a mutable lambda
    auto prefix_sum5 = compute_prefix_sum5(nums);
    assert_equal(prefix_sum5, prefix_sum_expected);

    // Method 6: using accumulate with a lambda that updates a vector
    auto prefix_sum6 = compute_prefix_sum6(nums);
    assert_equal(prefix_sum6, prefix_sum_expected);

    // Method 7: using for_each with a lambda that updates a vector
    auto prefix_sum7 = compute_prefix_sum7(nums);
    assert_equal(prefix_sum7, prefix_sum_expected);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
