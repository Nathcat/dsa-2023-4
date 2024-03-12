#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

/// @brief Perform a selection sort on an array
/// @tparam T The type contained by the array
/// @param array The array itself
/// @param n The number of items in the array
template <class T>
void selection_sort(T* array, int n) {
    for (int i = 0; i < n-1; i++) {
        int min_i = i;
        for (int j = i; j < n; j++) {
            if (array[j] < array[min_i]) {
                min_i = j;
            }
        }

        T tmp = array[i];
        array[i] = array[min_i];
        array[min_i] = tmp;
    }
}

#endif