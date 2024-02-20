#include <LinkedList.hpp>
#include <iostream>

int main() {
    int items[] = {1, 2, 3, 4};
    DoublyLinkedList<int>* list = DoublyLinkedList<int>::build(items, 4);

    list->for_each([](int index, int* item) {
        std::cout << index << ": " << *item << std::endl;
    });

    std::cout << std::endl << "Insert first" << std::endl;

    int item = 5;
    list->insert_first(&item);

    std::cout << "First: " << *(list->get_first()) << std::endl;

    list->for_each([](int index, int* item) {
        std::cout << index << ": " << *item << std::endl;
    });


    std::cout << std::endl << "Insert last" << std::endl;

    int item2 = 6;
    list->insert_last(&item2);

    std::cout << "Last: " << *(list->get_last()) << std::endl;

    list->for_each([](int index, int* item) {
        std::cout << index << ": " << *item << std::endl;
    });


    std::cout << std::endl << "Insert at 3" << std::endl;

    int item3 = 7;
    list->insert_at(3, &item3);

    std::cout << "3: " << *(list->get_at(3)) << std::endl;

    list->for_each([](int index, int* item) {
        std::cout << index << ": " << *item << std::endl;
    });


    std::cout << std::endl << "Remove last x2" << std::endl;

    list->remove_last();
    list->remove_last();

    list->for_each([](int index, int* item) {
        std::cout << index << ": " << *item << std::endl;
    });


    std::cout << std::endl << "Remove first x2" << std::endl;

    list->remove_first();
    list->remove_first();

    list->for_each([](int index, int* item) {
        std::cout << index << ": " << *item << std::endl;
    });


    std::cout << std::endl << "Remove 1" << std::endl;

    list->remove_at(1);

    list->for_each([](int index, int* item) {
        std::cout << index << ": " << *item << std::endl;
    });

    return 0;
};