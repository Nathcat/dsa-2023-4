#include <iostream>
#include <Testing.hpp>
#include <BinarySearch.hpp>

int main() {
    test<int>("Binary search when contained", []() {
        int items[] = {1, 1, 2, 2, 3, 4};
        return create_pair(0, binary_search<int>(1, items, 6));
    }, is_eq);

    test<int>("Binary search when not contained", []() {
        int items[] = {1, 1, 2, 2, 3, 4};
        return create_pair(-1, binary_search<int>(7, items, 6));
    }, is_eq);
}