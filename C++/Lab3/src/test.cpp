#include <stdio.h>
#include <LinkedStack.hpp>
#include <DynamicArrayList.hpp>
#include <iostream>
#include <Testing.hpp>

void linked_stack_test() {
    //  =======================
    //  Testing for LinkedStack
    //  =======================

    std::cout << "\n\n\t=======================\n\tTesting for LinkedStack\n\t=======================" << std::endl;

    test<int>("Push then get length", []() {
        int items[] = {1, 2, 3, 4};
        int top_item = 5;
        LinkedStack<int>* stack = LinkedStack<int>::build(items, 4);
        int length = stack->get_length();
        stack->push(top_item);
        return create_pair(length + 1, stack->get_length());
    }, is_eq);
    
    test<int>("Push then peek", []() {
        int items[] = {1, 2, 3, 4};
        int top_item = 5;
        LinkedStack<int>* stack = LinkedStack<int>::build(items, 4);
        stack->push(top_item);
        return create_pair(top_item, stack->peek());
    }, is_eq);

    test<int>("Push then pop", []() {
        int items[] = {1, 2, 3, 4};
        int top_item = 5;
        LinkedStack<int>* stack = LinkedStack<int>::build(items, 4);
        stack->push(top_item);
        return create_pair(top_item, stack->pop());
    }, is_eq);

    test<int>("Peek on empty stack", []() {
        LinkedStack<int>* stack = new LinkedStack<int>();
        try {
            stack->peek();
        } catch (int err) {
            return create_pair(LinkedStack<int>::STACK_IS_EMPTY, err);
        }
        return create_pair(0, -1);
    }, is_eq);

    test<int>("Peek then get length", []() {
        int items[] = {1, 2, 3, 4};
        int top_item = 5;
        LinkedStack<int>* stack = LinkedStack<int>::build(items, 4);
        int length = stack->get_length();
        stack->peek();
        return create_pair(length, stack->get_length());
    }, is_eq);

    test<int>("Peek then pop", []() {
        int items[] = {1, 2, 3, 4};
        int top_item = 5;
        LinkedStack<int>* stack = LinkedStack<int>::build(items, 4);
        return create_pair(stack->peek(), stack->pop());
    }, is_eq);

    test<int>("Pop on empty stack", []() {
        LinkedStack<int>* stack = new LinkedStack<int>();
        try {
            stack->pop();
        } catch (int err) {
            return create_pair(LinkedStack<int>::STACK_IS_EMPTY, err);
        }

        return create_pair(0, -1);
    }, is_eq);

    test<int>("Pop then get length", []() {
        int items[] = {1, 2, 3, 4};
        int top_item = 5;
        LinkedStack<int>* stack = LinkedStack<int>::build(items, 4);
        int length = stack->get_length();
        stack->pop();
        return create_pair(length - 1, stack->get_length());
    }, is_eq);
}

void dynamic_array_test() {
    //  ==============================
    //  Testing for dynamic array list
    //  ==============================
    std::cout << "\n\n\t==============================\n\tTesting for dynamic array list\n\t==============================" << std::endl;

    test<int>("Resize then get capacity", []() {
        int items[] = {1, 2, 3, 4};
        DynamicArrayList<int>* list = DynamicArrayList<int>::build(items, 4);

        int capacity = list->get_capacity();
        list->resize(6);
        return create_pair(6, list->get_capacity());
    }, is_eq);

    test<int>("Resize then get length", []() {
        int items[] = {1, 2, 3, 4};
        DynamicArrayList<int>* list = DynamicArrayList<int>::build(items, 4);
        int length = list->get_length();
        list->resize(6);
        return create_pair(length, list->get_length());
    }, is_eq);

    test<int>("Resize then get at", []() {
        int items[] = {1, 2, 3, 4};
        DynamicArrayList<int>* list = DynamicArrayList<int>::build(items, 4);
        int item = list->get_at(1);
        list->resize(6);
        return create_pair(item, list->get_at(1));
    }, is_eq);

    test<int>("Get at then remove at", []() {
        int items[] = {1, 2, 3, 4};
        DynamicArrayList<int>* list = DynamicArrayList<int>::build(items, 4);
        int v = list->get_at(1);
        return create_pair(v, list->remove_at(1));
    }, is_eq);

    test<int>("Insert at below lower bound", []() {
        int items[] = {1, 2, 3, 4};
        DynamicArrayList<int>* list = DynamicArrayList<int>::build(items, 4);

        try {
            list->insert_at(-1, 0);
        } catch (int err) {
            return create_pair(DynamicArrayList<int>::INDEX_ERROR, err);
        }

        return create_pair(0, -1);
    }, is_eq);

    test<int>("Insert at then get capacity", []() {
        int items[] = {1, 2, 3, 4};
        DynamicArrayList<int>* list = DynamicArrayList<int>::build(items, 4);
        list->resize(5);
        int old_capacity = list->get_capacity();
        int new_capacity = 10;
        list->insert_last(5);

        return create_pair(new_capacity, list->get_capacity());
    }, is_eq);
}

int main() {
    linked_stack_test();

    dynamic_array_test();

    return 0;
}