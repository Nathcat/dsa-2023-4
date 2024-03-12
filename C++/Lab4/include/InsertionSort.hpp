#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

/// @brief Sorts an array in place using the insertion sort
/// @tparam T The type contained by the array
/// @param array The array
/// @param n The number of items in the array
template <class T>
void insertion_sort(T* array, int n) {
    for (int i = 1; i < n; i ++) {
        for (int j = i; j > 0; j--) {
            if (array[j-1] > array[j]) {
                T tmp = array[j-1];
                array[j-1] = array[j];
                array[j] = tmp;
            }
            else {
                break;
            }
        }
    }
}

#endif