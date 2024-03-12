#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <Testing.hpp>
#include <cstring>
#include <stdlib.h>

template <class T>
struct ReturnPair {
    T* array;
    int n;
};

/// @brief Perform a merge sort on the given array
/// @tparam T The type contained by the array
/// @param array The array to sort
/// @param n The number of items in the array
/// @returns A value pair containing the pointer to the final array (a) and the number of items in the array (b)
template <class T>
struct ReturnPair<T> merge_sort(T* array, int n) {
    if (n == 1) return {array, 1};

    int mid = n / 2;
    T* first_half = (T*) malloc(mid * sizeof(T));
    T* second_half = (T*) malloc((n - mid) * sizeof(T));

    memcpy(first_half, array, mid * sizeof(T));
    memcpy(second_half, array + mid, (n - mid) * sizeof(T));

    struct ReturnPair<T> a_pair = merge_sort(first_half, mid);
    struct ReturnPair<T> b_pair = merge_sort(second_half, n - mid);

    T* A = a_pair.array; int An = a_pair.n;
    T* B = b_pair.array; int Bn = b_pair.n;
    T* merged_array = (T*) malloc(n * sizeof(T));

    int pA = 0;
    int pB = 0;
    int i = 0;
    while (i != n) {
        if (pA == An) {
            merged_array[i] = B[pB];
            pB++;
        }
        else if (pB == Bn) {
            merged_array[i] = A[pA];
            pA++;
        }
        else {
            if (A[pA] < B[pB]) {
                merged_array[i] = A[pA];
                pA++;
            }
            else {
                merged_array[i] = B[pB];
                pB++;
            }
        }

        i++;
    }

    return {merged_array, n};
}

#endif