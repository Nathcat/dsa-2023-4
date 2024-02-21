#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <DynamicArrayList.hpp>

template <class T>
class ArrayStack {
private:
    DynamicArrayList<T>* list;

public:
    static const int STACK_IS_EMPTY = 201;

    ArrayStack() {
        list = new DynamicArrayList<T>();
    }

    /// @brief Build a new stack from an existing array of items
    /// @param items The array of items
    /// @param length The number of items
    /// @return A new stack containing the provided items, and retaining the order they were presented in
    static ArrayStack<T>* build(T* items, int length) {
        ArrayStack<T>* stack = new ArrayStack<T>();
        stack->list = DynamicArrayList<T>::build(items, length);
        return stack;
    }

    /// @brief Get the capacity of the stack
    /// @return The total size of the internal array
    int get_capacity() {
        return this->list->get_capacity();
    }

    /// @brief Determine if the stack contains a certain item
    /// @param item The item to search for
    /// @return Boolean value describing wether or not the item was found in the stack
    int contains(T item) {
        return this->list->contains(item);
    }

    /// @brief Check if the stack is empty
    /// @return Boolean value describing wether or not the stack is empty.
    int is_empty() {
        return this->list->is_empty();
    }

    /// @brief Get the number of items in the stack
    /// @return The nummber of items in the stack
    int get_length() {
        return this->list->get_length();
    }

    /// @brief Push an item to the stack
    /// @param item The item to push to the stack
    void push(T item) {
        this->list->insert_first(item);
    }

    /// @brief Get the item at the top of the stack, without removing the item
    /// @return The item at the top of the stack
    T peek() {
        if (this->is_empty()) throw STACK_IS_EMPTY;
        return this->list->get_first();
    }

    /// @brief Get the item at the top of the stack, and remove it from the stack
    /// @return The item from the top of the stack.
    T pop() {
        if (this->is_empty()) throw STACK_IS_EMPTY;
        return this->list->remove_first();
    }

    /// @brief Call a function for every item in the stack, starting from the top of the stack
    /// @param f The function to call
    void for_each(void (*f)(int, T)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, this->list->get_at(i));
        }
    }

    /// @brief Call a function for every item in the stack, starting from the bottom of the stack
    /// @param f The function to call
    void reverse_for_each(void (*f)(int, T)) {
        for (int i = this->get_length() - 1; i >= 0; i++) {
            f(i, this->list->get_at(i));
        }
    }
};

#endif