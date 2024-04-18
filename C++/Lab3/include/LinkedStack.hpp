#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <LinkedList.hpp>

/// @brief Class representing a stack implementation using a singly linked list.
/// @tparam T The type contained by the stack
template <class T>
class LinkedStack {
private:
    LinkedList<T> list;

public:
    static const int STACK_IS_EMPTY = 201;

    /// @brief Build a new stack from an existing array of items.
    /// @param items The array of items
    /// @param length The length of the array
    /// @return A new stack containing the items in the provided array, maintaining the given order.
    static LinkedStack<T>* build(T* items, int length) {
        LinkedStack<T>* stack = new LinkedStack<T>();
        stack->list = LinkedList<T>::build(items, length);

        return stack;
    }

    /// @brief Check if the stack contains a certain item
    /// @return Boolean value describing wether or not the stack contains the given item
    int contains(T item) {
        for (int i = 0; i < this->get_length(); i++) {
            if (list->get_at(i) == item) {
                return 1;
            }
        }

        return 0;
    }

    /// @brief Check if the stack is empty
    /// @returns Boolean value describing wether or not the stack is empty.
    int is_empty() {
        return this->get_length() == 0;
    }
    
    /// @brief Get the number of items in the stack
    /// @return The number of items in the stack
    int get_length() {
        return list.get_length();
    }

    /// @brief Push an item to the stack
    /// @param item The item to push to the stack
    void push(T item) {
        list.insert_last(item);
    }

    /// @brief Return the item at the top of the stack without removing it
    /// @returns The item at the top of the stack
    /// @throws STACK_IS_EMPTY
    T peek() {
        if (this->is_empty()) throw STACK_IS_EMPTY;
        return list.get_last();
    }

    /// @brief Return the item at the top of the stack and remove it.
    /// @returns The item from the top of the stack
    /// @throws STACK_IS_EMPTY
    T pop() {
        if (this->is_empty()) throw STACK_IS_EMPTY;
        return list.remove_last();
    }

    /// @brief Call a function over every item in the stack.
    /// @param f The function to call
    void for_each(void (*f)(int, T)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, list.get_at(i));
        }
    }
};

#endif