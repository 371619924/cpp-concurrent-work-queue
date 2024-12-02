#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <random>

// Median-of-three pivot selection
template <class T>
int medianOfThree(std::vector<T>& vin, int& start, int& end) {
    int mid = start + (end - start) / 2; // Calculate the middle index
    if (vin[start] > vin[mid]) std::swap(vin[start], vin[mid]); // Ensure vin[start] <= vin[mid]
    if (vin[start] > vin[end]) std::swap(vin[start], vin[end]); // Ensure vin[start] <= vin[end]
    if (vin[mid] > vin[end]) std::swap(vin[mid], vin[end]);     // Ensure vin[mid] <= vin[end]
    return mid; // Return the index of the median value
}


template <class T>
int partition(std::vector<T>& vin, int start, int end) {
    if (vin[start] == vin[end]) {
        return (start + end) / 2; // Handle arrays where all elements are identical
    }
    int pivotIndex = medianOfThree(vin, start, end); // Select pivot using median-of-three
    T pivot = vin[pivotIndex];
    std::swap(vin[pivotIndex], vin[end]); // Move pivot to the end

    int i = start - 1; // Initialize the partition index
    for (int j = start; j < end; ++j) {
        if (vin[j] <= pivot) {
            ++i;
            if (i != j) std::swap(vin[i], vin[j]); // Swap if necessary to maintain partition order
        }
    }
    std::swap(vin[i + 1], vin[end]); // Move pivot to its correct position
    return i + 1; // Return the index of the pivot
}

// Use insertion sort for small subarrays
template <class T>
void insertionSort(std::vector<T>& vin, int start, int end) {
    for (int i = start + 1; i <= end; ++i) {
        T key = vin[i]; // Key to be inserted into the sorted portion
        int j = i - 1;
        while (j >= start && vin[j] > key) {
            vin[j + 1] = vin[j]; // Shift larger elements to the right
            j--;
        }
        vin[j + 1] = key; // Insert the key into its correct position
    }
}

// The main quicksort function
template <class T>
void quicksort(std::vector<T>& vin, int start = 0, int end = -1) {
    if (end == -1) end = vin.size() - 1; // Default to sorting the entire vector

    const int INSERTION_SORT_THRESHOLD = 20; // Threshold for switching to insertion sort
    while (start < end) {
        if (end - start <= INSERTION_SORT_THRESHOLD) {
            insertionSort(vin, start, end); // Use insertion sort for small subarrays
            break; // Exit the loop after sorting
        } else {
            int pivotIndex = partition(vin, start, end); // Partition the array around the pivot
            // Recur for the smaller partition first to minimize stack depth
            if (pivotIndex - start < end - pivotIndex) {
                quicksort(vin, start, pivotIndex - 1); // Sort the left partition
                start = pivotIndex + 1; // Update start to skip the sorted part
            } else {
                quicksort(vin, pivotIndex + 1, end); // Sort the right partition
                end = pivotIndex - 1; // Update end to skip the sorted part
            }
        }
    }
}

#endif 
