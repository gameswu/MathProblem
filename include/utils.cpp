#include "utils.h"
#include <cmath>
#include <vector>
#include <random>

std::vector<int> find_factors(int num, int digit)
{
    std::vector<int> factors;
    int start = pow(10, digit - 1);
    int end = pow(10, digit) - 1;

    for (int i = start; i <= end; ++i)
    {
        if (num % i == 0)
        {
            factors.push_back(i);
        }
    }

    return factors;
}

int find_a_factor(int num, int digit)
{
    std::vector<int> factors = find_factors(num, digit);
    if (factors.empty())
    {
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, factors.size() - 1);

    return factors[dist(gen)];
}