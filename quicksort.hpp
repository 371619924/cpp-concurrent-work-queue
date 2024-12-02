#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <vector>
#include <climits>
#include <iostream>

// Helper function to perform partitioning around a pivot
template <class T>
int partition(std::vector<T> &vin, int start, int end) {
    // Using the last element as the pivot
    T pivot = vin[end];
    int i = start - 1; // pointer for the smaller element
    for (int j = start; j < end; ++j) {
        // If current element is smaller than or equal to the pivot
        if (vin[j] <= pivot) {
            i++;
            std::swap(vin[i], vin[j]);
        }
    }
    std::swap(vin[i + 1], vin[end]); // Place the pivot in the correct position
    return i + 1; // Return the partition point
}

// The main quicksort function
template <class T>
inline void quicksort(std::vector<T> &vin, int start = INT_MIN, int end = INT_MIN) {
    // Set the initial start and end on the first call
    if (start == INT_MIN && end == INT_MIN) {
        start = 0;
        end = vin.size() - 1;
    }

    // Base case: return if the start index is not less than the end index
    if (start >= end) {
        return;
    }

    // Partition the array and get the pivot index
    int pivotIndex = partition(vin, start, end);

    // Recursively apply quicksort to the left and right subarrays
    quicksort(vin, start, pivotIndex - 1);
    quicksort(vin, pivotIndex + 1, end);
}

#endif
