#include <iostream>
#include <cstdlib>
#include <iomanip>

int
main(int argc, char* argv[])
{
    long long iterations = 1000000;
    if (argc > 1) {
        iterations = std::atoll(argv[1]);
    }

    double sum = 0.0;

    for (long long i = 0; i < iterations; ++i) {
        double term = 1.0 / (2.0 * i + 1.0);
        if (i % 2 == 0)
            sum += term;
        else
            sum -= term;
    }

    double pi = 4.0 * sum;

    std::cout << std::setprecision(15);
    std::cout << pi << "\n";
}
