#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

/// @brief A Linked List node.
/// @tparam T The data type contained by the node.
template <class T>
class Node
{
public:
    T *data;
    Node<T> *next;

    Node()
    {
        data = nullptr;
        next = nullptr;
    }

    Node(T *data, Node<T> *next)
    {
        this->data = data;
        this->next = next;
    }
};

/// @brief A Linked List node which contains a pointer to the previous element as well as the next.
/// @tparam T The data tyoe contained by the node.
template <class T>
class DoubleNode : public Node<T>
{
public:
    Node<T> *prev;

    DoubleNode(T *data, Node<T> *prev, Node<T> *next)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

/// @brief Class representing a general Linked List.
/// @tparam T The type contained by the list.
template <class T>
class LinkedList
{
public:
    //  I don't like making these fields public but I don't have much of a choice with the implementation I'm going for.
    //  We either have nice inheritance for each kind of linked list, or we have more appropriate access modifiers on these fields,
    //  and I have chose nice inheritance.

    /// @brief The first node in the linked list. SHOULD NOT BE MODIFIED DIRECTLY
    Node<T> *first_node = nullptr;
    /// @brief The last node in the linked list. SHOULD NOT BE MODIFIED DIRECTLY
    Node<T> *last_node = nullptr;
    /// @brief The length of the linked list, i.e. the number of items. SHOULD NOT BE MODIFIED DIRECTLY
    int length = 0;

    /// @brief Make this linked list contain a single item.
    /// @param sole_item The single item to contain.
    void make_singleton(T *sole_item);

    /// @brief Determines whether or not the list contains a certain item.
    /// @param item The item to search for
    /// @return Boolean value describing wether or not the item is present in the list.
    int contains(T item)
    {
        Node<T> *current_node = first_node;

        while (current_node != nullptr && *(current_node->data) != item)
        {
            current_node = current_node->next;
        }

        return current_node != nullptr;
    }

    /// @brief Determines if the list is empty or not
    /// @return Boolean value describing wether the list is empty or not.
    int is_empty()
    {
        return length == 0;
    }

    /// @brief Get the length of the list.
    /// @return The length of the list.
    int get_length()
    {
        return length;
    }

    /// @brief Get the first node of the list.
    /// @return The first node of the list.
    Node<T> *get_first_node()
    {
        return first_node;
    }

    /// @brief Get the first item in the list, which contained by the first node.
    /// @return The first item in the list.
    T *get_first()
    {
        return first_node->data;
    }

    /// @brief Get the node at the given index.
    /// @param index The index.
    /// @return The node at the given index.
    Node<T> *get_node_at(int index)
    {
        int i = 0;
        Node<T> *current_node = first_node;

        while (current_node != nullptr && i != index)
        {
            current_node = current_node->next;
            i++;
        }

        return current_node;
    }

    /// @brief Get the item at the given index.
    /// @param index The index.
    /// @return The item contained by the node at the given index.
    T *get_at(int index)
    {
        return this->get_node_at(index)->data;
    }

    /// @brief Get the last node in the list.
    /// @return The last node in the list
    Node<T> *get_last_node()
    {
        return last_node;
    }

    /// @brief Get the last item in the list, contained by the last node.
    /// @return The last item in the list.
    T *get_last()
    {
        return last_node->data;
    }

    /// @brief Set the first item in the list
    /// @param item The item to set as the first item
    void set_first(T *item)
    {
        first_node->data = item;
    }

    /// @brief Set the item at the given index.
    /// @param index The index to set the item to.
    /// @param item The item to assign to the given index.
    void set_at(int index, T *item)
    {
        this->get_node_at(index)->data = item;
    }

    /// @brief Set the last item in the list
    /// @param item The item to set to be the last item in the list.
    void set_last(T *item)
    {
        last_node->data = item;
    }

    /// @brief Insert the given item to the front of the list.
    /// @param item The item to insert
    void insert_first(T *item);

    /// @brief Insert the given item to the given index.
    /// @param index The index to insert the item at.
    /// @param item The item to insert.
    void insert_at(int index, T *item);

    /// @brief Insert the given item to the end of the last
    /// @param item The item to insert
    void insert_last(T *item);

    /// @brief Remove the first item in the list
    /// @return The item which was removed
    T *remove_first();

    /// @brief Remove the item at the given index in the list.
    /// @param index The index of the item to remove.
    /// @return The item which was removed.
    T *remove_at(int index);

    /// @brief Remove the last item in the list
    /// @return The item which was removed.
    T *remove_last();

    /// @brief Call the given function for every node in the list
    /// @param f The function to call for each node.
    void for_each(void (*f)(int, Node<T> *))
    {
        Node<T> *current_node = first_node;
        int i = 0;

        while (current_node != nullptr)
        {
            f(i, current_node);
            current_node = current_node->next;
            i++;
        }
    }

    /// @brief Call teh given function for every item in the list
    /// @param f The function to call for each item
    void for_each(void (*f)(int, T *))
    {
        Node<T> *current_node = first_node;
        int i = 0;

        while (current_node != nullptr)
        {
            f(i, current_node->data);
            current_node = current_node->next;
            i++;
        }
    }
};

/// @brief Class representing a Singly Linked List.
/// @tparam T The type contained by the list.
template <class T>
class SinglyLinkedList : public LinkedList<T>
{
public:
    /// @brief Build a singly linked list from an existing array of items
    /// @param items The array of items
    /// @param length The length of the array
    /// @return A singly linked list which contains the items in the given array, in the order presented.
    static SinglyLinkedList<T> *build(T *items, int length)
    {
        SinglyLinkedList<T> *list = new SinglyLinkedList<T>();
        for (int i = 0; i < length; i++)
        {
            list->insert_last(items + i);
        }

        return list;
    };

    /// @brief Create a singly linked list of one item
    /// @param sole_item The single item to include in the list
    void make_singleton(T *sole_item)
    {
        Node<T> *node = new Node<T>(sole_item, nullptr);
        ((LinkedList<T> *)this)->first_node = node;
        ((LinkedList<T> *)this)->last_node = node;
        ((LinkedList<T> *)this)->length = 1;
    };

    /// @brief Insert an item to the front of the list
    /// @param item The item to insert
    void insert_first(T *item)
    {
        if (this->is_empty())
        {
            this->make_singleton(item);
            return;
        }

        Node<T> *new_node = new Node<T>(item, ((LinkedList<T> *)this)->first_node);
        ((LinkedList<T> *)this)->first_node = new_node;
        ((LinkedList<T> *)this)->length++;
    }

    /// @brief Insert an item at the given index.
    /// @param index The index to insert at.
    /// @param item The item to insert.
    void insert_at(int index, T *item)
    {
        if (index == 0)
        {
            if (this->is_empty())
            {
                this->make_singleton(item);
                return;
            }

            this->insert_first(item);
            return;
        }
        else if (index == ((LinkedList<T> *)this)->length)
        {
            this->insert_last(item);
            return;
        }

        Node<T> *new_node = new Node<T>(item, this->get_node_at(index));
        this->get_node_at(index - 1)->next = new_node;
        ((LinkedList<T> *)this)->length++;
    }

    /// @brief Insert an item to the end of the list.
    /// @param item The item to be inserted.
    void insert_last(T *item)
    {
        if (this->is_empty())
        {
            this->make_singleton(item);
            return;
        }

        Node<T> *new_node = new Node<T>(item, nullptr);
        ((LinkedList<T> *)this)->last_node->next = new_node;
        ((LinkedList<T> *)this)->last_node = new_node;
        ((LinkedList<T> *)this)->length++;
    }

    /// @brief Remove the first item from the list
    /// @return The item which was removed
    T *remove_first()
    {
        T *item = ((LinkedList<T> *)this)->first_node->data;
        ((LinkedList<T> *)this)->first_node = ((LinkedList<T> *)this)->first_node->next;
        ((LinkedList<T> *)this)->length--;
        return item;
    }

    /// @brief Remove the item at the given index.
    /// @param index The index to remove at.
    /// @return The item which was removed.
    T *remove_at(int index)
    {
        T *item = this->get_node_at(index)->data;
        this->get_node_at(index - 1)->next = this->get_node_at(index)->next;
        ((LinkedList<T> *)this)->length--;
        return item;
    }

    /// @brief Remove the last item in the list.
    /// @return The item which was removed.
    T *remove_last()
    {
        T *item = ((LinkedList<T> *)this)->last_node->data;
        this->get_node_at(((LinkedList<T> *)this)->length - 2)->next = nullptr;
        ((LinkedList<T> *)this)->length--;
        return item;
    }
};

/// @brief Class containing a doubly linked list.
/// @tparam T The type contained by the list.
template <class T>
class DoublyLinkedList : public LinkedList<T>
{
public:
    /// @brief Build a doubly linked list from an existing array of items.
    /// @param items The array of items
    /// @param length The length of the array
    /// @return A doubly linked list containing all the items from the given array, retaining the original ordering of the items.
    static DoublyLinkedList<T> *build(T *items, int length)
    {
        std::cout << "Building list" << std::endl;
        DoublyLinkedList<T> *list = new DoublyLinkedList<T>();
        for (int i = 0; i < length; i++)
        {
            std::cout << "Inserting " << i << std::endl;
            list->insert_last(items + i);
        }

        return list;
    }

    /// @brief Reconstruct this list to contain only one item.
    /// @param sole_item The only item that the list should contain.
    void make_singleton(T *sole_item)
    {
        DoubleNode<T> *node = new DoubleNode<T>(sole_item, nullptr, nullptr);
        this->first_node = node;
        this->last_node = node;
        this->length = 1;
    }

    /// @brief Insert an item to the front of the array
    /// @param item The item to insert
    void insert_first(T *item)
    {
        if (this->is_empty()) {
            this->make_singleton(item);
            return;
        }

        DoubleNode<T> *node = new DoubleNode<T>(item, nullptr, this->first_node);
        ((DoubleNode<T>*) this->first_node)->prev = node;
        this->first_node = node;
        this->length++;
    }

    /// @brief Insert an item to the given index in the list.
    /// @param item The item to insert
    /// @param index The index to insert the item at
    void insert_at(int index, T *item)
    {
        if (index == 0) {
            this->insert_first(item);
            return;
        }
        else if (index == this->length) {
            this->insert_last(item);
        }

        DoubleNode<T> *current_node = ((DoubleNode<T>*) this->first_node);
        int i = 0;
        while (current_node != nullptr && i != index)
        {
            current_node = (DoubleNode<T> *)((DoubleNode<T> *)current_node)->next;
            i++;
        }

        if (i == index)
        {
            DoubleNode<T> *node = new DoubleNode<T>(item, current_node->prev, current_node->next);
            current_node->prev->next = node;
            current_node->prev = node;
            this->length++;
        }

        // Else index is not in the range of the list
    }

    /// @brief Insert an item to the end of the list
    /// @param item The item to insert
    void insert_last(T *item)
    {
        if (this->is_empty()) {
            this->make_singleton(item);
            return;
        }

        DoubleNode<T> *node = new DoubleNode<T>(item, this->last_node, nullptr);
        this->last_node->next = node;
        this->last_node = node;
        this->length++;
    }

    /// @brief Remove the first item in the list
    /// @return The item which was removed
    T *remove_first()
    {
        T *item = this->first_node->data;
        ((DoubleNode<T>*) this->first_node)->prev = nullptr;
        this->first_node = (DoubleNode<T> *)((DoubleNode<T> *)this->first_node)->next;
        this->length--;
        return item;
    }

    /// @brief Remove the item at the given index
    /// @param index The index to remove
    /// @return The item which was removed
    T *remove_at(int index)
    {
        if (index == 0) {
            return this->remove_first();
        }
        else if (index == this->length - 1) {
            return this->remove_last();
        }

        DoubleNode<T> *current_node = (DoubleNode<T>*) this->first_node;
        int i = 0;
        while (current_node != nullptr && i != index)
        {
            current_node = (DoubleNode<T> *)((DoubleNode<T> *)current_node)->next;
            i++;
        }

        if (i == index)
        {
            T *item = current_node->data;
            current_node->prev->next = current_node->next;
            this->length--;
            return item;
        }

        // Else index is not in the range of the list
        return nullptr;
    }

    /// @brief Remove the last item in the list
    /// @return The item which was removed
    T *remove_last()
    {
        T *item = this->last_node->data;
        ((DoubleNode<T>*) this->last_node)->prev->next = nullptr;
        this->last_node = (DoubleNode<T> *)((DoubleNode<T> *)this->last_node)->prev;
        this->length--;
        return item;
    }

    void reverse_for_each(void (*f)(int, T*)) {
        DoubleNode<T>* current_node = this->last_node;

        for (int i = this->length - 1; i >= 0; i--) {
            f(i, current_node->data);
            current_node = current_node->prev;
        }
    }

    void reverse_for_each(void (*f)(int, DoubleNode<T>*)) {
        DoubleNode<T>* current_node = this->last_node;

        for (int i = this->length - 1; i >= 0; i--) {
            f(i, current_node);
            current_node = current_node->prev;
        }
    }
};

#endif