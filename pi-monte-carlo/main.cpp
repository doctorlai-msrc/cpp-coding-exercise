#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

static std::uint64_t
count_hits(std::uint64_t n, std::uint64_t seed)
{
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::uint64_t hits = 0;
    for (std::uint64_t i = 0; i < n; ++i) {
        const double x = dist(rng);
        const double y = dist(rng);
        if (x * x + y * y <= 1.0)
            ++hits;
    }
    return hits;
}

int
main(int argc, char* argv[])
{
    int threads = 2;
    std::uint64_t n = 1'000'000;

    if (argc > 1)
        threads = std::max(1, std::atoi(argv[1]));
    if (argc > 2)
        n = std::max<std::uint64_t>(1, std::strtoull(argv[2], nullptr, 10));

    const std::uint64_t base = n / threads;
    const std::uint64_t rem = n % threads;

    std::vector<std::thread> pool;
    std::vector<std::uint64_t> hits(threads, 0);

    // a single nondeterministic seed source; each thread gets a different seed
    std::random_device rd;
    const std::uint64_t master_seed = (static_cast<std::uint64_t>(rd()) << 32) ^ static_cast<std::uint64_t>(rd());

    for (int i = 0; i < threads; ++i) {
        const std::uint64_t points = base + (static_cast<std::uint64_t>(i) < rem ? 1 : 0);
        const std::uint64_t seed = master_seed + 0x9e3779b97f4a7c15ULL * static_cast<std::uint64_t>(i + 1);

        pool.emplace_back([&, i, points, seed] { hits[i] = count_hits(points, seed); });
    }

    for (auto& t : pool)
        t.join();

    const std::uint64_t total_hits = std::accumulate(hits.begin(), hits.end(), std::uint64_t{0});
    const long double pi = 4.0 * static_cast<long double>(total_hits) / static_cast<long double>(n);

    std::cout << pi << "\n";
    return 0;
}