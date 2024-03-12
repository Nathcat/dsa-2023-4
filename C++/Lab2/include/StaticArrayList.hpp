#ifndef STATIC_ARRAYLIST_H
#define STATIC_ARRAYLIST_H

#include <cstring>
#include <stdlib.h>

/// @brief An array list implementation using static arrays
/// @tparam T The type contained by the list
template <class T>
class StaticArrayList {
private:
    /// @brief The internal array containing items
    T* array;
    /// @brief The number of items in the internal array
    int n;

public:
    static const int LIST_IS_EMPTY = 201;
    static const int INDEX_ERROR = 202;

    StaticArrayList() {
        this->array = nullptr;
        this->n = 0;
    }

    /// @brief Build a new array list from an existing array of items
    /// @param items The array of items
    /// @param n The number of items in the array
    /// @return A new array list containing the specified items, retaining the same order
    static StaticArrayList<T>* build(T* items, int n) {
        StaticArrayList<T>* list = new StaticArrayList();
        list->array = items;
        list->n = n;

        return list;
    }

    /// @brief Turn this list into a list of one item
    /// @param item The one item to contain
    void make_singleton(T item) {
        this->array = (T*) malloc(sizeof(T));
        this->n = 1;
        this->array[0] = item;
    }

    /// @brief Check if the array lsit contains a certain item
    /// @param item The item to search for
    /// @return true or false
    int contains(T item) {
        for (int i = 0; i < this->n; i++) {
            if (this->array[i] == item) return 1;
        }

        return 0;
    }

    /// @brief Check if the list is empty
    /// @return true or false
    int is_empty() {
        return this->n == 0;
    }

    /// @brief Get the number of items in the list
    /// @return The number of items in the list
    int get_length() {
        return this->n;
    }

    /// @brief Get the internal array pointer
    /// @return Pointer to the internal array
    T* get_internal_array() {
        return this->array;
    }

    /// @brief Get the first item in the list
    /// @return The first item in the list
    /// @throws LIST_IS_EMPTY
    T get_first() {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        return this->array[0];
    }

    /// @brief Get the item at an index in the list
    /// @param index The index of the item
    /// @return The item at that index
    /// @throws INDEX_ERROR
    T get_at(int index) {
        if (index < 0 || index >= this->n) throw INDEX_ERROR;
        return this->array[index];
    }

    /// @brief Get the last item in the list
    /// @return The last item in the list
    /// @throws LIST_IS_EMPTY
    T get_last() {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        return this->array[this->n-1];
    }

    /// @brief Set the first item in the list
    /// @param item The item to set as the first item
    /// @throws LIST_IS_EMPTY
    void set_first(T item) {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        this->set_at(0, item);
    }

    /// @brief Set the item at an index
    /// @param index The index to set at
    /// @param item The item to set
    /// @throws INDEX_ERROR
    void set_at(int index, T item) {
        if (index < 0 || index >= this->n) throw INDEX_ERROR;
        this->array[index] = item;
    }

    /// @brief Set the last item in the list
    /// @param item The item to set as the last item
    /// @throws LIST_IS_EMPTY
    void set_last(T item) {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        this->set_at(n-1, item);
    }

    /// @brief Insert an item to the front of the list
    /// @param item The item to insert
    void insert_first(T item) {
        if (this->array == nullptr) {
            this->make_singleton(item);
            return;
        }

        this->insert_at(0, item);
    }

    /// @brief Insert an item at a given index
    /// @param index The index to insert at
    /// @param item The item to insert
    /// @throws INDEX_ERROR
    void insert_at(int index, T item) {
        if (index < 0 || index > n) throw INDEX_ERROR;
        
        T* new_array = (T*) malloc((this->n+1) * sizeof(T));
        memcpy(new_array, this->array, index * sizeof(T));
        memcpy(new_array + index + 1, this->array + index, (n - index) * sizeof(T));

        new_array[index] = item;
        this->array = new_array;
        this->n++;
    }

    /// @brief Insert an item to the end of the list
    /// @param item The item to insert
    void insert_last(T item) {
        if (this->array == nullptr) {
            this->make_singleton(item);
            return;
        }

        this->insert_at(n, item);
    }

    /// @brief Remove the first item in the list
    /// @return The item which was just removed
    /// @throws LIST_IS_EMPTY
    T remove_first() {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        return this->remove_at(0);
    }

    /// @brief Remove the item at the given index
    /// @param index The index of the item to remove
    /// @return The item which was removed
    /// @throws INDEX_ERROR
    T remove_at(int index) {
        if (index < 0 || index >= this->n) throw INDEX_ERROR;

        T item = this->get_at(index);

        if (this->n == 1) {
            this->array = nullptr;
            this->n = 0;
            return item;
        }

        T* new_array = (T*) malloc((this->n-1) * sizeof(T));
        memcpy(new_array, this->array, (index-1) * sizeof(T));
        memcpy(new_array + index, this->array + index + 1, (this->n - index - 1) * sizeof(T));

        this->array = new_array;
        this->n--;
        return item;
    }

    /// @brief Remove the last item in the list
    /// @return The item which was removed
    /// @throws LIST_IS_EMPTY
    T remove_last() {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        return this->remove_at(this->n-1);
    }

    /// @brief Call a function for every item in the list, starting from the start of the list
    /// @param f The function to call
    void for_each(void (*f)(int, T)) {
        for (int i = 0; i < this->n; i++) {
            f(i, this->get_at(i));
        }
    }

    /// @brief Call a function for every item in the list, starting from the end of the list
    /// @param f The function to call
    void reverse_for_each(void (*f)(int, T)) {
        for (int i = this->n-1; i >= 0; i--) {
            f(i, this->get_at(i));
        }
    }
};

#endif