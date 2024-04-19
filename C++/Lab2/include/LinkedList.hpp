#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

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
        *value = value;
        prev = nullptr;
        next = nullptr;
    }

    DoublyLinkedNode(T v, DoublyLinkedNode<T>* prev, DoublyLinkedNode<T>* next) {
        value = (T*) malloc(sizeof(T));
        *value = value;
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

public:
    static const int LIST_IS_EMPTY = 201;
    static const int INDEX_ERROR = 202;

    DoublyLinkedList() {
        first_node = nullptr;
        last_node = nullptr;
    }

    /// @brief Build a new linked list from an existing set of items
    /// @param items The set of items
    /// @param n The number of items in the set
    /// @return The new list
    static DoublyLinkedList<T> build(T* items, int n) { throw 100; }

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

    void set_first(T item) {}

    void set_at(int i, T item) {}

    void set_last(T item) {}

    void insert_first(T item) {}

    void insert_at(int i, T item) {}

    void insert_last(int i, T item) {}

    T remove_first() {}

    T remove_at(int i) {}

    T remove_last() {}

    void for_each(void (*f)(int, DoublyLinkedNode<T>*)) {}

    void for_each(void (*f)(int, T)) {}
};

#endif