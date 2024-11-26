#ifndef _PRIMES_H
#define _PRIMES_H

#include <vector>
#include <ranges>
#include <iterator>
#include <climits>
#include <iostream>



class Primes
{
    static std::vector<long long> allprimes;

    static bool isprime(long long value)
    {
        (void) value;
        std::cout << "IMPLEMENT ME!\n";
        return false;
    }

    static void calculate_next_prime()
    {
        std::cout << "IMPLEMENT ME!\n";  
    }

    size_t index;

public:
    // Needed to fully map the forward_iterator concept
    using difference_type = long long;
    using element_type = long long; // element_type is a reserved name that must be used in the definition
    using pointer = element_type *;
    using reference = element_type &;
    using iterator_category = std::bidirectional_iterator_tag;

    // Default constructor is required to pass forward_iterator assertion
    Primes(int i = 0) : index(i) {}

    // Copy constructor copies the index
    Primes(const Primes &p) : index(p.index){}

    Primes &operator++()
    {
        index++;
        return *this;
    }
    Primes operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    Primes &operator--()
    {
        index--;
        return *this;
    }
    Primes operator--(int)
    {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator!=(const Primes &p) const
    {
        return index != p.index;
    }
    bool operator==(const Primes &p) const
    {
        return index == p.index;
    }

    long long operator*() const
    {
        std::cout << "IMPLEMENT ME!\n";  
        return 0;
    }

    // Iterator traits:
    Primes begin()
    {
        return *this;
    }
    Primes end()
    {
        return Primes(INT_MAX);
    }

};

static_assert(std::bidirectional_iterator<Primes>);
static_assert(std::input_iterator<Primes>);
static_assert(std::forward_iterator<Primes>);
static_assert(!std::random_access_iterator<Primes>);

inline auto primerange()
{
    return std::ranges::subrange{Primes().begin(), Primes().end()};
}

#endif