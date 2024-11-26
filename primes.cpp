#include "primes.hpp"

// Needed to make C++ happy, you can't initialize
// the static members in the .hpp file (static values 
// initialized in the header need to be initialized by a 
// constexpr value, and you can't have that for a 
// newly allocated vector.

std::vector<long long> Primes::allprimes = {2};

