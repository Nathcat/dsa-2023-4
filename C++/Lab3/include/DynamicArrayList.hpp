#ifndef DYNAMICARRAYLIST_H
#define DYNAMICARRAYLIST_H

#include <stdlib.h>
#include <cstring>

template <class T>
class DynamicArrayList {
private:
    /// @brief The array containing the data
    T* array;

    /// @brief The number of items contained in the list
    int length;

    /// @brief The actual capacity of the internal array
    int capacity;

    /// @brief Check if the internal array should grow
    void grow_if_should() {
        if (this->length == this->capacity) {
            if (this->capacity == 0) {
                this->resize(1);
            }
            else {
                this->resize(2 * this->capacity);
            }
        }
    }

    /// @brief Check if the internal array hsould shrink
    void shrink_if_should() {
        if (this->length <= this->capacity / 4) {
            this->resize(this->capacity / 2);
        }
    }

public:
    static const int INDEX_ERROR = 201;
    static const int LIST_IS_EMPTY = 202;
    static const int VALUE_ERROR = 203;

    DynamicArrayList() {
        this->length = 0;
        this->capacity = 1;
        this->array = (T*) malloc(sizeof(T));
    }

    /// @brief Build a new array list from an existing array of items
    /// @param items The array of items
    /// @param length The length of the given array of items
    /// @return A new array list containing all the given items, in the order they were presented
    static DynamicArrayList<T>* build(T* items, int length) {
        DynamicArrayList<T>* list = new DynamicArrayList<T>();

        for (int i = 0; i < length; i++) {
            list->insert_last(items[i]);
        }

        return list;
    }

    /// @brief Resize the internal array to the given size
    /// @param new_capacity The new size of the internal array
    /// @throws VALUE_ERROR
    void resize(int new_capacity) {
        if (new_capacity < length) throw VALUE_ERROR;
        T* new_array = (T*) malloc(new_capacity * sizeof(T));
        memcpy(new_array, this->array, this->length * sizeof(T));
        this->capacity = new_capacity;
    }

    /// @brief Set the capacity of the internal array to match the number of items in the list
    void shrink_to_fit() {
        this->resize(this->length);
    }

    /// @brief Check if the list contains the given item
    /// @param item The item to search for
    /// @return Boolean value describing wether or not the list contains the given value.
    int contains(T item) {
        for (int i = 0; i < this->length; i++) {
            if (item == this->get_at(i)) return 1;
        }

        return 0;
    }

    /// @brief Test if the list is empty
    /// @return Boolean value describing wether or not the list is empty,
    int is_empty() {
        return this->length == 0;
    }

    /// @brief Get the length of the list
    /// @return The number of items in the list (the length)
    int get_length() {
        return this->length;
    }

    /// @brief Get the capacity of the internal array
    /// @return The capacity of the internal array
    int get_capacity() {
        return this->capacity;
    }

    /// @brief Get the first item in the list
    /// @return The first item in the list
    /// @throws LIST_IS_EMPTY
    T get_first() {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        return this->get_at(0);
    }

    /// @brief Get the item at the given index
    /// @param index The index of the item to get
    /// @return The item at the given index.
    /// @throws INDEX_ERROR
    T get_at(int index) {
        if (index < 0 || index >= this->length) throw INDEX_ERROR;
        return this->array[index];
    }

    /// @brief Get the last item in the list
    /// @return The last item in the list
    /// @throws LIST_IS_EMPTY
    T get_last() {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        return this->get_at(this->length - 1);
    }

    /// @brief Set the first item in the list
    /// @param item The item to set as the first in the list
    /// @throws LIST_IS_EMPTY
    void set_first(T item) {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        this->set_at(0, item);
    }

    /// @brief Set the item at the given index in the list
    /// @param index The index to set at
    /// @param item The item to set at the index
    /// @throws INDEX_ERROR
    void set_at(int index, T item) {
        if (index < 0 || index >= this->length) throw INDEX_ERROR;
        this->array[index] = item;
    }

    /// @brief Set the last item in the list
    /// @param item The item to set as the last in the list
    /// @throws LIST_IS_EMPTY
    void set_last(T item) {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        this->set_at(this->length - 1, item);
    }

    /// @brief Insert an item to the front of the list
    /// @param item The item to insert
    void insert_first(T item) {
        T* new_array = (T*) malloc(this->capacity * sizeof(T));
        memcpy(new_array + 1, this->array, this->length * sizeof(T));
        this->array = new_array;
        this->array[0] = item;
        this->length++;
        this->grow_if_should();
    }

    /// @brief Insert an item to an index in the list
    /// @param index The index to insert to
    /// @param item The item to insert at the index
    /// @throws INDEX_ERROR
    void insert_at(int index, T item) {
        if (index == 0) {
            this->insert_first(item);
            return;
        }
        else if (index == this->length) {
            this->insert_last(item);
            return;
        }
        else if (index < 0 || index > this->length) {
            throw INDEX_ERROR;
        }

        T* new_array = (T*) malloc(this->capacity * sizeof(T));
        memcpy(new_array, this->array, index * sizeof(T));
        memcpy(new_array + index + 1, this->array + index, (this->length - index - 1) * sizeof(T));
        new_array[index] = item;
        this->array = new_array;
        this->length++;
        this->grow_if_should();
    }

    /// @brief Insert an item to the end of the list
    /// @param item The item to insert
    void insert_last(T item) {
        this->length++;
        this->array[this->length - 1] = item;
        this->grow_if_should();
    }

    /// @brief Remove the first item in the list
    /// @return The item which was removed
    /// @throws LIST_IS_EMPTY
    T remove_first() {
        if (this->is_empty()) throw LIST_IS_EMPTY;

        T item = this->get_at(0);
        T* new_array = (T*) malloc(this->capacity * sizeof(T));
        memcpy(new_array, this->array + 1, (--this->length) * sizeof(T));
        this->array = new_array;
        this->shrink_if_should();
        return item;
    }

    /// @brief Remove an item at an index in the list
    /// @param index The index to remove at
    /// @return The item which was removed
    /// @throws INDEX_ERROR
    T remove_at(int index) {
        if (index == 0) {
            return this->remove_first();
        }
        else if (index == this->length - 1) {
            return this->remove_last();
        }
        else if (index < 0 || index >= this->length) {
            throw INDEX_ERROR;
        }
        
        T item = this->get_at(index);
        T* new_array = (T*) malloc(this->capacity * sizeof(T));
        memcpy(new_array, this->array, index * sizeof(T));
        memcpy(new_array + index, this->array + index + 1, (this->length - index - 1) * sizeof(T));
        this->array = new_array;
        this->length--;
        this->shrink_if_should();
        return item;
    }

    /// @brief Remove the last item in the list
    /// @return The item which was removed
    /// @throws LIST_IS_EMPTY
    T remove_last() {
        if (this->is_empty()) throw LIST_IS_EMPTY;
        this->length--;
        return this->array[this->length];
    }

    /// @brief Call a function for every item in the list, starting from the start of the list
    /// @param f The function to call
    void for_each(void (*f)(int, T)) {
        for (int i = 0; i < this->length; i++) {
            f(i, this->get_at(i));
        }
    }

    /// @brief Call a function for every item in the list, starting from the end of the list
    /// @param f The function to call
    void reverse_for_each(void (*f)(int, T)) {
        for (int i = this->length - 1; i >= 0; i--) {
            f(i, this->get_at(i));
        }
    }

};

#endif