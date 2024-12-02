#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <random>
#include <utility>

// Helper function to perform partitioning around a pivot
template <class T>
int partition(std::vector<T>& vin, int start, int end) noexcept {
    // Randomly choose a pivot to avoid worst-case O(n^2) performance
    int pivotIndex = start + rand() % (end - start + 1);
    T pivot = std::move(vin[pivotIndex]);
    std::swap(vin[pivotIndex], vin[end]); // Move pivot to the end

    int i = start - 1;
    for (int j = start; j < end; ++j) {
        if (vin[j] <= pivot) {
            ++i;
            std::swap(vin[i], vin[j]); // Efficient swap
        }
    }
    std::swap(vin[i + 1], vin[end]); // Place pivot at the correct position
    return i + 1;
}

// Insertion sort for small subarrays
template <class T>
void insertionSort(std::vector<T>& vin, int start, int end) noexcept {
    for (int i = start + 1; i <= end; ++i) {
        T key = std::move(vin[i]);
        int j = i - 1;
        while (j >= start && vin[j] > key) {
            vin[j + 1] = std::move(vin[j]);
            --j;
        }
        vin[j + 1] = std::move(key);
    }
}

// Tail-recursive quicksort
template <class T>
void quicksort_internal(std::vector<T>& vin, int start, int end) noexcept {
    while (start < end) {
        if (end - start <= 10) { // Use insertion sort for small arrays
            insertionSort(vin, start, end);
            return;
        }

        int pivotIndex = partition(vin, start, end);

        // Tail-recursive optimization: sort the smaller subarray first
        if (pivotIndex - start < end - pivotIndex) {
            quicksort_internal(vin, start, pivotIndex - 1);
            start = pivotIndex + 1; // Move to the right subarray
        } else {
            quicksort_internal(vin, pivotIndex + 1, end);
            end = pivotIndex - 1; // Move to the left subarray
        }
    }
}

// Main quicksort function
template <class T>
inline void quicksort(std::vector<T>& vin) noexcept {
    if (vin.size() <= 1) return; // Already sorted
    quicksort_internal(vin, 0, vin.size() - 1);
}

#endif
