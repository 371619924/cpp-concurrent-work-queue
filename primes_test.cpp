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
TEST(PrimesTest, TestMemoization){
long long testprimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
auto index = 0;
for (auto i : primerange() | std::views::take(500000))
{
if (i < 30)
{
EXPECT_EQ(i, testprimes[index++]);
}
}
auto second = std::chrono::system_clock::now();
for (auto i : primerange() | std::views::drop(499999) | std::views::take(1))
{
std::cout << i << "\n";
ASSERT_EQ(i, 7368787);
}
auto third = std::chrono::system_clock::now();
auto t1 = std::chrono::duration_cast<std::chrono::microseconds>(third -
second).count();
ASSERT_TRUE(t1 < 10000);
}
