#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <vector>
#include <climits>


// So we don't need a separate function we have start and end set to INT_MIN
// for determining we need to start the sorting.
template <class T>
inline void quicksort(std::vector<T> &vin, int start=INT_MIN, int end=INT_MIN){
    (void) vin;
    (void) start;
    (void) end;
    std::cout << "IMPLEMENT THIS!\n"
}


#endif