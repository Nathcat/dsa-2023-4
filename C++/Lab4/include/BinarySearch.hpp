#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <iostream>

/// @brief Perform a binary search
/// @tparam T The type contained within the target array
/// @param target The target item to search for
/// @param array The array to search
/// @param n The number of items in the array
/// @return The index of the item in the array, or -1 if it is not present
template <class T>
int binary_search(T target, T* array, int n) {
    int pL, pR, mid;
    pL = 0;
    pR = n - 1;

    while (pL <= pR) {
        mid = (pL + pR) / 2;

        if (array[mid] > target) {
            pR = mid - 1;
        }
        else if (array[mid] < target) {
            pL = mid + 1;
        }
        else {
            return mid;
        }
    }

    return -1;

}

#endif