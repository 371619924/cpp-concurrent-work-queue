#include <gtest/gtest.h>

#include "primes.hpp"
#include <ranges>

TEST(PrimesTest, TestBasic)
{
    long long testprimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    auto index = 0;
    for (auto i : primerange() | std::views::take(50000))
    {
        std::cout << i << "\n";
        if (i < 30)
        {
            EXPECT_EQ(i, testprimes[index++]);
        }
    }
    for (auto i : primerange() | std::views::drop(49999) | std::views::take(1))
    {
        std::cout << i << "\n";
    }

}