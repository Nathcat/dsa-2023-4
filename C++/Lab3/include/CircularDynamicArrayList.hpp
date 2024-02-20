#include <stdlib.h>
#include <iostream>
#include <cstring>

template <class T> class CircularDynamicArrayList {
private:
    T* array;
    int first_index = 0;
    int length = 0;
    int capacity;

    void grow_if_should() {
        int capacity = this->get_capacity();
        if (this->length == capacity) {
            if (capacity == 0) {
                this->resize(1);
            }
            else {
                this->resize(2 * capacity);
            }
        }
    }

    void shrink_if_should() {
        if (this->length <= this->get_capacity() / 4) {
            this->resize(this->get_capacity() / 2);
        }
    }

public:

    CircularDynamicArrayList(int capacity, int length) {
        this->capacity = capacity;
        this->array = (T*) malloc(sizeof(T) * capacity);
        this->length = length;
    }

    template <class Type> static CircularDynamicArrayList<Type>* build(Type* items, int capacity) {
        CircularDynamicArrayList<Type>* list = new CircularDynamicArrayList<Type>(capacity, capacity);

        for (int i = 0; i < capacity; i++) {
            list->set_at(i, items[i]);
        }

        return list;
    }

    void shrink_to_fit() {
        resize(length);
    }

    int contains(T item) {
        for (int i = 0; i < length; i++) {
            if (get_at(i) == item) {
                return 1;
            }
        }

        return 0;
    }

    int is_empty() {
        return length == 0;
    }

    int get_length() {
        return length;
    }

    int get_capacity() {
        return capacity;
    }

    void for_each(void (*f)(int, T)) {
        for (int i = 0; i < length; i++) {
            f(i, this->get_at(i));
        }
    }

    CircularDynamicArrayList<T>* copy() {
        CircularDynamicArrayList<T>* list = new CircularDynamicArrayList<T>(capacity, length);
        memcpy(list->array, array, capacity * sizeof(T));
        list->first_index = first_index;
        return list;
    }

    //
    // All from here are implemented as part of the lab
    //

    void resize(int new_capacity) {
        T* new_array = (T*) malloc(sizeof(T) * new_capacity);
        for (int i = 0; i < length; i++) {
            new_array[i] = get_at(i);
        }

        array = new_array;
        capacity = new_capacity;
        first_index = 0;
    }

    T get_first() {
        return get_at(0);
    }

    T get_last() {
        return get_at(length - 1);
    }

    T get_at(int index) {
        return array[(index + first_index) % capacity];
    }

    void set_first(T item) {
        set_at(0, item);
    }

    void set_last(T item) {
        set_at(length - 1, item);
    }

    void set_at(int index, T item) {
        array[(index + first_index) % capacity] = item;
    }

    void insert_first(T new_first_item) {
        if (length == capacity) grow_if_should();

        first_index--;
        if (first_index < 0) first_index = capacity - 1;

        array[first_index] = new_first_item;
        length++;
    }

    void insert_last(T new_last_item) {
        if (length == capacity) grow_if_should();

        array[(first_index + length) % capacity] = new_last_item;
        length++;
    }

    void insert_at(int index, T new_item) {
        if (length == capacity) grow_if_should();

        if (index == 0) {
            this->insert_first(new_item);
            return;
        }
        else if (index == length - 1) {
            this->insert_last(new_item);
            return;
        }

        CircularDynamicArrayList<T>* copy = this->copy();

        for (int i = 0, j = 0; i < length + 1; i++) {
            if (i == index) {
                array[(i + first_index) % capacity] = new_item;
                continue;
            }

            array[(i + first_index) % capacity] = copy->get_at(j);
            j++;
        }

        length++;
    }

    T remove_first() {
        T item = this->get_at(0);
        first_index++; length--;
        shrink_if_should();
        return item;
    }

    T remove_last() {
        T item = this->get_at(length - 1);
        length--;
        shrink_if_should();
        return item;
    }

    T remove_at(int index) {
        CircularDynamicArrayList<T>* copy = this->copy();
        T item = this->get_at(index);
        for (int i, j = 0; i < length - 1; i++) {
            if (i == index) {
                j++;
            }

            array[(i + first_index) % capacity] = copy->get_at(j);
            j++;
        }
        
        length -= 1;
        this->shrink_if_should();
        return item;
    }
};