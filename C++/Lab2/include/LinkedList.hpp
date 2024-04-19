#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

template <class T>
class SinglyLinkedNode {
public:
    T* value;
    SinglyLinkedNode<T>* next;

    SinglyLinkedNode() {
        value = nullptr;
        next = nullptr;
    }

    SinglyLinkedNode(T value) {
        this->value = (T*) malloc(sizeof(T));
        *this->value = value;
        next = nullptr;
    }

    SinglyLinkedNode(T value, SinglyLinkedNode<T>* next) {
        this->value = (T*) malloc(sizeof(T));
        *this->value = value;
        this->next = next;
    }

    SinglyLinkedNode(SinglyLinkedNode<T>& n) {
        this->value = n.value;
        this->next = n.next;
    }

    SinglyLinkedNode(SinglyLinkedNode<T>&& n) {
        this->value = n.value;
        this->next = n.next;
        n.value = nullptr;
        n.next = nullptr;
    }

    SinglyLinkedNode<T>& operator=(SinglyLinkedNode<T>& n) {
        this->value = n.next;
        this->next = n.next;
        return *this;
    }

    SinglyLinkedNode<T>&& operator=(SinglyLinkedNode<T>&& n) {
        this->value = n.value;
        this->next = n.next;
        n.value = nullptr;
        n.next = nullptr;
        return *this;
    }
};

template <class T>
class DoublyLinkedNode {
public:
    T* value;
    DoublyLinkedNode<T>* prev;
    DoublyLinkedNode<T>* next;

    DoublyLinkedNode() {
        value = nullptr;
        prev = nullptr;
        next = nullptr;
    }

    DoublyLinkedNode(T v) {
        value = (T*) malloc(sizeof(T));
        *value = v;
        prev = nullptr;
        next = nullptr;
    }

    DoublyLinkedNode(T v, DoublyLinkedNode<T>* prev, DoublyLinkedNode<T>* next) {
        value = (T*) malloc(sizeof(T));
        *value = v;
        this->prev = prev;
        this->next = next;
    }

    ~DoublyLinkedNode() {
        value = nullptr;
        prev = nullptr;
        next = nullptr;
    }

    DoublyLinkedNode(DoublyLinkedNode<T>& n) {
        value = n.value;
        prev = n.prev;
        next = n.prev;
    }

    DoublyLinkedNode(DoublyLinkedNode<T>&& n) {
        value = n.value;
        prev = n.prev;
        next = n.next;
        n.value = nullptr;
        n.prev = nullptr;
        n.next = nullptr;
    }

    DoublyLinkedNode<T>& operator=(DoublyLinkedNode<T>& n) {
        value = n.value;
        prev = n.prev;
        next = n.prev;
        return *this;
    }

    DoublyLinkedNode<T>&& operator=(DoublyLinkedNode<T>&& n) {
        value = n.value;
        prev = n.prev;
        next = n.prev;
        n.value = nullptr;
        n.prev = nullptr;
        n.next = nullptr;
        return *this;
    }
};

template <class T>
class LinkedList {
private:
    SinglyLinkedNode<T>* first_node = nullptr;
    SinglyLinkedNode<T>* last_node = nullptr;
    int length = 0;

    SinglyLinkedNode<T>* get_node(int i) {
        SinglyLinkedNode<T>* current_node = first_node;
        int index = 0;

        while (index != i) {
            current_node = current_node->next;
            index++;
        }

        return current_node;
    }

    void reset_last_node() {
        SinglyLinkedNode<T>* n = first_node;
        while (n->next != nullptr) {
            n = n->next;
        }

        last_node = n;
    }

public:
    static const int LIST_IS_EMPTY = 201;
    static const int INDEX_ERROR = 202;

    /// @brief Build a new linked list from the given array of items
    /// @param items The array of items
    /// @param length The length of the array
    /// @return The new list
    static LinkedList<T> build(T* items, int length) {
        LinkedList<T> l;

        for(int i = 0; i < length; i++) {
            l.insert_last(items[i]);
        }

        return l;
    }

    /// @brief Create a new list with only one item
    /// @param item The item
    /// @return The new list which contains only the given item
    static LinkedList<T> make_singleton(T item) {
        return LinkedList<T>::build(&item, 1);
    }

    /// @brief Get the length of the linked list
    /// @return The length of the linked list
    int get_length() {
        return length;
    }

    /// @brief Check if the linked list contains the given item.
    /// @param item The item to search for.
    /// @return Whether or not the list contains the given item.
    bool contains(T item) {
        SinglyLinkedNode<T>* current_node = first_node;
        while (current_node != nullptr) {
            if (*(current_node->value) == item) return true;

            current_node = current_node->next;
        }

        return false;
    }

    /// @brief Check if the linked list is empty or not.
    /// @return Whether or not the linked list is empty.
    bool is_empty() {
        return length == 0;
    }

    /// @brief Get the first item in the list
    /// @return The first item in the list
    /// @throws LIST_IS_EMPTY
    T get_first() {
        return get_at(0);
    }

    /// @brief Get the value at a given index in the list
    /// @param i The index to get
    /// @return The value at the given index
    /// @throws LIST_IS_EMPTY and INDEX_ERROR
    T get_at(int i) {
        if (is_empty()) throw LIST_IS_EMPTY;
        if (i >= length || i < 0) throw INDEX_ERROR;

        // Because of the final condition it is not possible for
        // the first node to be nullptr here, and the requested
        // index will be within the range of the list.
        SinglyLinkedNode<T>* current_node = first_node;
        int index = 0;

        while (index != i) {
            current_node = current_node->next;
            index++;
        }

        return *current_node->value;
    }

    /// @brief Get the last item in the list
    /// @return The last item in the list
    /// @throws LIST_IS_EMPTY
    T get_last() {
        return get_at(length - 1);
    }

    /// @brief Set the first item in the list
    /// @param item The item to set
    /// @throws LIST_IS_EMPTY
    void set_first(T item) {
        set_at(0, item);
    }

    /// @brief Set the item at the given index in the list
    /// @param i The index to set at
    /// @param item The item to set
    /// @throws LIST_IS_EMPTY and INDEX_ERROR
    void set_at(int i, T item) {
        if (is_empty()) throw LIST_IS_EMPTY;
        if (i >= length || i < 0) throw INDEX_ERROR;

        SinglyLinkedNode<T>* current_node = first_node;
        int index = 0;

        while (index != i) {
            current_node = current_node->next;
            index++;
        }

        *current_node->value = item;
    }

    /// @brief Set the last item in the list
    /// @param item The list item to set
    /// @throws LIST_IS_EMPTY
    void set_last(T item) {
        set_at(length - 1, item);
    }

    /// @brief Insert a new item to the front of the last
    /// @param item The item to insert
    void insert_first(T item) {
        insert_at(0, item);
    }

    /// @brief Insert a new item at the given index in the list
    /// @param i The index to insert at
    /// @param item The item to insert
    /// @throws INDEX_ERROR
    void insert_at(int i, T item) {
        if (i > length || i < 0) throw INDEX_ERROR;
        if (i == 0) {
            SinglyLinkedNode<T>* n = new SinglyLinkedNode<T>(item, first_node);
            first_node = n;
            length++;
            reset_last_node();
            return;
        }

        SinglyLinkedNode<T>* prev = get_node(i - 1);
        SinglyLinkedNode<T>* n = new SinglyLinkedNode<T>(item, prev->next);
        prev->next = n;
        length++;
        reset_last_node();
    }

    /// @brief Insert a new item at the end of the list
    /// @param item The item to insert
    void insert_last(T item) {
        insert_at(length, item);
    }

    /// @brief Remove the first item in the list and return it
    /// @return The item which was just removed from the list
    /// @throws LIST_IS_EMPTY
    T remove_first() {
        return remove_at(0);
    }

    /// @brief Remove the item at the given index
    /// @param i The index in the list to remove
    /// @return The item which was removed
    /// @throws LIST_IS_EMPTY and INDEX_ERROR
    T remove_at(int i) {
        if (is_empty()) throw LIST_IS_EMPTY;
        if (i > length || i < 0) throw INDEX_ERROR;

        if (i == 0) {
            T* d = first_node->value;
            first_node = first_node->next;
            length--;
            return *d;
        }

        SinglyLinkedNode<T>* n = first_node;
        int index = 0;
        
        while (index != i-1) {
            n = n->next;
            index++;
        }
        
        T* d = n->next->value;
        n->next = n->next->next;
        length--;
        return *d;
    }

    /// @brief Remove the last item in the list
    /// @return The item which was just removed
    T remove_last() {
        return remove_at(length - 1);
    }

    void for_each(void (*f)(int, SinglyLinkedNode<T>*)) {
        int i = 0;
        SinglyLinkedNode<T>* n = first_node;

        while (n != nullptr) {
            f(i++, n);
            n = n->next;
        }
    }

    void for_each(void (*f)(int, T)) {
        int i = 0; 
        SinglyLinkedNode<T>* n = first_node;

        while (n != nullptr) {
            f(i++, *(n->value));
            n = n->next;
        }
    }
};


template <class T>
class DoublyLinkedList {
private:
    DoublyLinkedNode<T>* first_node;
    DoublyLinkedNode<T>* last_node;
    int length = 0;

    void check_edge_nodes() {
        // I would have made this method recursive or repeat in some way, but it will be called whenever the
        // nodes of the list are manipulated and that can only happen one at a time.

        // These two cases may appear when using insert_first or last
        if (first_node == nullptr && last_node != nullptr) first_node = last_node;
        if (last_node == nullptr && first_node != nullptr) last_node = first_node;

        // Check the first node
        if (first_node->prev != nullptr) {
            first_node = first_node->prev;
        }

        if (first_node->next != nullptr && first_node->next->prev == nullptr) {
            first_node = first_node->next;
        }

        // Check the last node
        if (last_node->prev != nullptr) {
            last_node = last_node->prev;
        }

        if (last_node->next != nullptr && last_node->next->prev == nullptr) {
            last_node = last_node->next;
        }
    }

public:
    static const int LIST_IS_EMPTY = 201;
    static const int INDEX_ERROR = 202;

    DoublyLinkedList() {
        first_node = nullptr;
        last_node = nullptr;
    }

    DoublyLinkedList(DoublyLinkedList<T>& l) {
        first_node = l.first_node;
        last_node = l.last_node;
        length = l.length;
    }

    DoublyLinkedList(DoublyLinkedList<T>&& l) {
        first_node = l.first_node;
        last_node = l.last_node;
        length = l.length;
        l.first_node = nullptr;
        l.last_node = nullptr;
    }

    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>& l) {
        first_node = l.first_node;
        last_node = l.last_node;
        length = l.length;
        return *this;
    }

    DoublyLinkedList<T>&& operator=(DoublyLinkedList<T>&& l) {
        first_node = l.first_node;
        last_node = l.last_node;
        length = l.length;
        l.first_node = nullptr;
        l.last_node = nullptr;
        return *this;
    }

    /// @brief Build a new linked list from an existing set of items
    /// @param items The set of items
    /// @param n The number of items in the set
    /// @return The new list
    static DoublyLinkedList<T> build(T* items, int n) {
        DoublyLinkedList<T>* l = new DoublyLinkedList<T>();
        for (int i = 0; i < n; i++) {
            l->insert_last(items[i]);
        }

        return *l;
    }

    /// @brief Build a new linked list containing only one item
    /// @param item The only item
    /// @return The new linked list which contains only one item
    static DoublyLinkedList<T> make_singleton(T item) {
        DoublyLinkedList<T>* l = new DoublyLinkedList<T>();
        l->insert_first(item);
        return *l;
    }

    /// @brief Get the length of the linked list
    /// @return The length of the list
    int get_length() {
        return length;
    }

    /// @brief Check whether the list contains a certain item
    /// @param item The item to search for
    /// @return Whether or not the list contains the given item
    bool contains(T item) {
        DoublyLinkedNode<T>* n = first_node;
        while (n != nullptr) {
            if (*n->value == item) return true;

            n = n->next;
        }

        return false;
    }

    /// @brief Check if the list is empty
    /// @return Whether or not the list is empty
    bool is_empty() {
        return length == 0;
    }

    /// @brief Get the first item in the list
    /// @return The first item in the list
    /// @throws LIST_IS_EMPTY
    T get_first() {
        return get_at(0);
    }

    /// @brief Get the item at the given index in the list
    /// @param i The index of the item
    /// @return The item at index i
    /// @throws LIST_IS_EMPTY and INDEX_ERROR
    T get_at(int i) {
        if (is_empty()) throw LIST_IS_EMPTY;
        if (i < 0 || i >= length) throw INDEX_ERROR;

        if (i > length / 2) {
            // Move backwards through the list
            DoublyLinkedNode<T>* n = last_node;
            int ind = length - 1;
            while (ind != i) {
                n = n->prev;
                ind--;
            }

            return *n->value;
        }
        else {
            // Move forwards through the list
            DoublyLinkedNode<T>* n = first_node;
            int ind = 0;
            while (ind != i) {
                n = n->next;
                ind++;
            }

            return *n->value;
        }
    }

    /// @brief Get the item at the end of the list
    /// @return The item at the end of the list
    /// @throws LIST_IS_EMPTY
    T get_last() {
        return get_at(length - 1);
    }

    /// @brief Set the first item in the list to be the given item
    /// @param item The given item to set
    /// @throws LIST_IS_EMPTY
    void set_first(T item) {
        set_at(0, item);
    }

    /// @brief Set the item at the given index
    /// @param i The index to set
    /// @param item The item to set
    /// @throws LIST_IS_EMPTY and INDEX_ERROR
    void set_at(int i, T item) {
        if (is_empty()) throw LIST_IS_EMPTY;
        if (i < 0 || i >= length) throw INDEX_ERROR;

        DoublyLinkedNode<T>* n = first_node;
        int N = 0;
        while (N != i) {
            n = n->next;
            N++;
        }

        *n->value = item;
    }

    /// @brief Set the last item in the list to the given item
    /// @param item The item to set 
    /// @throws LIST_IS_EMPTY
    void set_last(T item) {
        set_at(length - 1, item);
    }

    /// @brief Insert an item to the start o the list
    /// @param item The item to insert
    void insert_first(T item) {
        DoublyLinkedNode<T>* n = new DoublyLinkedNode<T>(item, nullptr, first_node);
        if (first_node != nullptr) { first_node->prev = n; } else { last_node = n; }
        first_node = n;
        length++;
    }

    /// @brief Insert an item to the given index in the list
    /// @param i The index to insert at
    /// @param item The item to insert
    /// @throws INDEX_ERROR
    void insert_at(int i, T item) {
        if (i < 0 || i > length) throw INDEX_ERROR;
        if (i == 0) { insert_first(item); return; }
        if (i == length) { insert_last(item); return; }

        // 0 < i < length

        DoublyLinkedNode<T>* n = first_node;
        int N = 0;
        while (N != i-1) {
            n = n->next;
            N++;
        }

        // Because of the precondtions n is guaranteed to NOT be either the first or last node, hence the invariant:
        // n->prev != nullptr && n->next != nullptr

        DoublyLinkedNode<T>* newNode = new DoublyLinkedNode<T>(item, n, n->next);
        n->next->prev = newNode;
        n->next = newNode;

        length++;
    }

    /// @brief Insert an item to the end of the list
    /// @param item The item to insert
    void insert_last(T item) {
        DoublyLinkedNode<T>* n = new DoublyLinkedNode<T>(item, last_node, nullptr);
        if (last_node != nullptr) { last_node->next = n; } else { first_node = n; }
        last_node = n;
        length++;
    }

    /// @brief Remove the first item from the list
    /// @return The item which was just removed
    /// @throws LIST_IS_EMPTY
    T remove_first() {
        if (is_empty()) throw LIST_IS_EMPTY;

        T item = *first_node->value;
        if (first_node->next == nullptr) {
            length--;  // Should be 0 now
            first_node = nullptr; last_node = nullptr;
            return item;
        }

        first_node->next->prev = nullptr;
        first_node = first_node->next;
        length--;
        return item;
    }

    /// @brief Remove the item at the given index in the list
    /// @param i The index of the item to remove
    /// @return The item which was removed
    /// @throws LIST_IS_EMPTY and INDEX_ERROR
    T remove_at(int i) {
        if (is_empty()) throw LIST_IS_EMPTY;
        if (i < 0 || i >= length) throw INDEX_ERROR;
        if (i == 0) return remove_first();
        if (i == length-1) return remove_last();

        DoublyLinkedNode<T>* n = first_node;
        int N = 0;
        while (N != i) {
            n = n->next;
            N++;
        }

        n->prev->next = n->next;
        length--;
        check_edge_nodes();
        return *n->value;
    }

    /// @brief Remove the last item in the list
    /// @return The item which was removed
    /// @throws LIST_IS_EMPTY
    T remove_last() {
        if (is_empty()) throw LIST_IS_EMPTY;
        
        T item = *last_node->value;
        if (last_node->prev == nullptr) {
            length--;  // Should be 0 now
            first_node = nullptr; last_node = nullptr;
            return item;
        }

        last_node->prev->next = nullptr;
        last_node = last_node->prev;
        length--;
        return item;
    }

    void for_each(void (*f)(int, DoublyLinkedNode<T>*)) {
        DoublyLinkedNode<T>* n = first_node;
        int i = 0;
        while (n != nullptr) {
            f(i++, n); n = n->next;
        }
    }

    void for_each(void (*f)(int, T)) {
        DoublyLinkedNode<T>* n = first_node;
        int i = 0;
        while (n != nullptr) {
            f(i++, *n->value); n = n->next;
        }
    }

    void for_each_reverse(void (*f)(int, DoublyLinkedNode<T>*)) {
        DoublyLinkedNode<T>* n = last_node;
        int i = length - 1;
        while (n != nullptr) {
            f(i--, n); n = n->prev;
        }
    }

    void for_each_reverse(void (*f)(int, T)) {
        DoublyLinkedNode<T>* n = last_node;
        int i = length - 1;
        while (n != nullptr) {
            f(i--, *n->value); n = n->prev;
        }
    }
};

#endif