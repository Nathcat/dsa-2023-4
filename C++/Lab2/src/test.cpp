#include <LinkedList.hpp>
#include <iostream>
#include <Testing.hpp>
#include <random>
#include <time.h>

int main() {
    srand(time(NULL));

    test<int>("Get at below lower bound", []() {
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> l = LinkedList<int>::build(items, 5);

        try {
            l.get_at(-1);
        } catch (int err) {
            return create_pair(LinkedList<int>::INDEX_ERROR, err);
        }

        return create_pair(-1, -1);
    }, is_eq);

    test<int>("Get at", []() {
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> l = LinkedList<int>::build(items, 5);

        int r = rand() % 5;
        return create_pair(items[r], l.get_at(r));
    }, is_eq);

    test<int>("Insert at", []() {
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> l = LinkedList<int>::build(items, 5);

        int r = rand() % 5;
        l.insert_at(r, 6);

        return create_pair(6, l.get_at(r));
    }, is_eq);

    test<int>("Insert at end", []() {
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> l = LinkedList<int>::build(items, 5);

        l.insert_at(l.get_length(), 6);

        return create_pair(6, l.get_at(l.get_length() - 1));
    }, is_eq);

    test<int>("Insert when empty", []() {
        LinkedList<int> l;

        l.insert_first(1);
        return create_pair(1, l.get_at(0));
    }, is_eq);

    test<int>("Remove on empty", []() {
        LinkedList<int> l;

        try {
            int v = l.remove_first();
        } catch (int err) {
            return create_pair(LinkedList<int>::LIST_IS_EMPTY, err);
        }
        return create_pair(-1, -1);
    }, is_eq);

    test<int>("Remove first", []() {
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> l = LinkedList<int>::build(items, 5);

        return create_pair(items[0], l.remove_first());
    }, is_eq);

    test<int>("Remove last", []() {
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> l = LinkedList<int>::build(items, 5);

        return create_pair(items[4], l.remove_last());
    }, is_eq);

    test<int>("Remove at", []() {
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> l = LinkedList<int>::build(items, 5);

        int r = rand() % 5;
        std::cout << "Removing " << r << std::endl;
        return create_pair(items[r], l.remove_at(r));
    }, is_eq);
}