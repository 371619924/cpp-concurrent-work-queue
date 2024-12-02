#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <vector>
#include <climits>
#include <iostream>
#include <random>  // C++11 中的随机数生成器

// Helper function to perform partitioning around a pivot
template <class T>
int partition(std::vector<T>& vin, int start, int end) {
    // 使用 C++11 的随机数生成器来提高效率
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);
    int pivotIndex = dis(gen);  // Random pivot selection
    T pivot = vin[pivotIndex];
    std::swap(vin[pivotIndex], vin[end]);  // Move pivot to the end

    int i = start - 1;
    for (int j = start; j < end; ++j) {
        if (vin[j] <= pivot) {
            i++;
            if (i != j) {  // Avoid unnecessary swap
                std::swap(vin[i], vin[j]);
            }
        }
    }
    if (i + 1 != end) {  // Avoid unnecessary swap
        std::swap(vin[i + 1], vin[end]);
    }
    return i + 1;
}


// Insertion sort for small subarrays
template <class T>
void insertionSort(std::vector<T>& vin, int start, int end) {
    for (int i = start + 1; i <= end; ++i) {
        T key = std::move(vin[i]);  // Use move semantics to avoid unnecessary copies
        int j = i - 1;
        while (j >= start && vin[j] > key) {
            vin[j + 1] = std::move(vin[j]);  // Use move semantics here too
            j--;
        }
        vin[j + 1] = std::move(key);  // Move the key to its final position
    }
}


// The main quicksort function
template <class T>
inline void quicksort(std::vector<T>& vin, int start = INT_MIN, int end = INT_MIN) {
    if (start == INT_MIN && end == INT_MIN) {
        start = 0;
        end = vin.size() - 1;
    }

    const int INSERTION_SORT_THRESHOLD = 10;

    if (end - start <= INSERTION_SORT_THRESHOLD) {
        insertionSort(vin, start, end);  // Use insertion sort for small subarrays
    } else {
        int pivotIndex = partition(vin, start, end);
        // 选择递归调用较小的子数组进行优化，尾递归优化
        if (pivotIndex - start < end - pivotIndex) {
            quicksort(vin, start, pivotIndex - 1);
            quicksort(vin, pivotIndex + 1, end);
        } else {
            quicksort(vin, pivotIndex + 1, end);
            quicksort(vin, start, pivotIndex - 1);
        }
    }
}

#endif
