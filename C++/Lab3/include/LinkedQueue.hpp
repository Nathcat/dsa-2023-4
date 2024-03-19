#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <LinkedList.hpp>

/// @brief Class representing a queue implementation using a singly linked list.
/// @tparam T The type contained by the queue
template <class T>
class LinkedQueue {
private:
    SinglyLinkedList<T>* list;

public:
    static const int QUEUE_IS_EMPTY = 201;
    
    LinkedQueue() {
        list = new SinglyLinkedList<T>();
    }

    /// @brief Build a new queue from an existing array of items.
    /// @param items The array of items
    /// @param length The length of the array
    /// @return A new queue containing the items in the provided array, maintaining the given order.
    static LinkedQueue<T>* build(T* items, int length) {
        LinkedQueue<T>* queue = new LinkedQueue<T>();
        queue->list = SinglyLinkedList<T>::build(items, length);

        return queue;
    }

    /// @brief Check if the queue contains a certain item
    /// @return Boolean value describing wether or not the queue contains the given item
    int contains(T item) {
        for (int i = 0; i < this->get_length(); i++) {
            if (list->get_at(i) == item) {
                return 1;
            }
        }

        return 0;
    }

    /// @brief Check if the queue is empty
    /// @returns Boolean value describing wether or not the queue is empty.
    int is_empty() {
        return this->get_length() == 0;
    }
    
    /// @brief Get the number of items in the queue
    /// @return The number of items in the queue
    int get_length() {
        return list->get_length();
    }

    /// @brief Push an item to the queue
    /// @param item The item to push to the queue
    void push(T item) {
        list->insert_last(item);
    }

    /// @brief Return the item at the top of the queue without removing it
    /// @returns The item at the top of the queue
    /// @throws QUEUE_IS_EMPTY
    T* peek() {
        if (this->is_empty()) throw QUEUE_IS_EMPTY;
        return list->get_first();
    }

    /// @brief Return the item at the top of the queue and remove it.
    /// @returns The item from the top of the queue
    /// @throws QUEUE_IS_EMPTY
    bool pop(T** out) {
        if (this->is_empty()) throw QUEUE_IS_EMPTY;
        return list->remove_first(out);
    }

    /// @brief Call a function over every item in the queue.
    /// @param f The function to call
    void for_each(void (*f)(int, T)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, list->get_at(i));
        }
    }
};

#endif