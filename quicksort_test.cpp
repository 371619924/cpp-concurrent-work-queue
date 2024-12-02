#include "quicksort.hpp"
#include <gtest/gtest.h>
#include <ranges>
#include <chrono>
#include <algorithm>
#include <random>
TEST(QuicksortTest, TestBasic)
{
auto rng = std::default_random_engine();
for(auto i : std::views::iota(0,100)){
(void) i;
std::vector<int> test;
for(auto j : std::views::iota(0, 100)){
test.push_back(j);
}
std::shuffle(test.begin(), test.end(), rng);
quicksort(test);
for(auto j : std::views::iota(0,100)){
ASSERT_EQ(test[j], j);
}
}
std::vector<int> test2;
for(auto j : std::views::iota(0,100000)){
test2.push_back(j);
}
std::shuffle(test2.begin(), test2.end(), rng);
quicksort(test2);
}
TEST(QuicksortTest, TestPathology){
auto rng = std::default_random_engine();
std::vector<int> test, test2;
for(auto j : std::views::iota(0, 100000)){
test.push_back(j);
test2.push_back(42);
}
auto startpathology = std::chrono::system_clock::now();
quicksort(test);
quicksort(test2);
auto stoppathology = std::chrono::system_clock::now();
std::shuffle(test.begin(), test.end(), rng);
auto startnormal = std::chrono::system_clock::now();
quicksort(test);
auto stopnormal = std::chrono::system_clock::now();
auto normaltime =
std::chrono::duration_cast<std::chrono::microseconds>(stopnormal -
startnormal).count();
auto pathologicaltime =
std::chrono::duration_cast<std::chrono::microseconds>(stoppathology -
startpathology).count();
EXPECT_TRUE(pathologicaltime < (normaltime * 2.2));
}
