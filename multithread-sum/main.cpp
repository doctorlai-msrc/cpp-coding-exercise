/**
This demonstrates a simple multithreaded sum calculation using C++11 threads.
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <stdexcept>   // for exceptions
#include <limits>

using SumT = unsigned long long;

int main(int argc, char* argv[])
{
    std::size_t data_size = 1'000'000;
    std::size_t num_threads = 4;

    if (argc == 3) {
        try {
            long long ds = std::stoll(argv[1]);
            long long nt = std::stoll(argv[2]);
            if (ds < 0 || nt <= 0) {
                throw std::invalid_argument("data_size must be >= 0 and num_threads must be > 0");
            }
            data_size = static_cast<std::size_t>(ds);
            num_threads = static_cast<std::size_t>(nt);
        } catch (const std::exception& e) {
            std::cerr << "Invalid arguments: " << e.what() << "\n"
                      << "Usage: " << argv[0] << " <data_size> <num_threads>\n";
            return 1;
        }
    } else if (argc != 1) {
        std::cerr << "Usage: " << argv[0] << " <data_size> <num_threads>\n";
        return 1;
    }

    if (num_threads == 0) return 1;
    if (data_size == 0) {
        std::cout << "Total Sum: 0\nExpected Sum: 0\n";
        return 0;
    }

    // Avoid spawning more threads than elements (optional but sensible).
    if (num_threads > data_size) num_threads = data_size;

    // Guard against int overflow in iota values.
    if (data_size > static_cast<std::size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "data_size too large for vector<int> initialization via iota.\n";
        return 1;
    }

    std::vector<int> data(data_size);
    std::iota(data.begin(), data.end(), 1);

    std::vector<SumT> partial_sums(num_threads, 0);
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    const std::size_t block_size = data_size / num_threads;

    for (std::size_t i = 0; i < num_threads; ++i) {
        const std::size_t start = i * block_size;
        const std::size_t end = (i == num_threads - 1) ? data_size : start + block_size;

        threads.emplace_back([&, i, start, end] {
            partial_sums[i] = std::accumulate(data.begin() + start, data.begin() + end, SumT{0});
            std::cout << "Thread processing range [" << start << ", " << end
                      << ") computed local sum: " << partial_sums[i] << "\n";
        });
    }

    for (auto& t : threads) t.join();

    const SumT global_sum = std::accumulate(partial_sums.begin(), partial_sums.end(), SumT{0});
    std::cout << "Total Sum: " << global_sum << "\n";

    const SumT expected_sum = static_cast<SumT>(data_size) * (static_cast<SumT>(data_size) + 1) / 2;
    std::cout << "Expected Sum: " << expected_sum << "\n";

    assert(expected_sum == global_sum);
    return 0;
}
