#include <iostream>
#include <Testing.hpp>
#include <BinaryTree.hpp>
#include <random>
#include <time.h>


int main() {
    srand(time(0));

    test<bool>("Contains on empty tree", []() {
        BTree::BinaryTree<int> tree;

        int a = 5;
        return create_pair(false, tree.contains(&a));
    }, is_eq);

    test<bool>("Insert then contains", []() {
        BTree::BinaryTree<int> tree;
        std::cout << "Created tree" << std::endl;
        int a = 5;
        tree.insert(&a);
        std::cout << "Inserted" << std::endl;

        tree.depth_for_each([](int i, int v) {
            std::cout << i << ": " << v << std::endl;
        });

        int b = 5;
        return create_pair(true, tree.contains(&b));
    }, is_eq);

    test<bool>("Insert the not contains", []() {
        BTree::BinaryTree<int> tree;
        int a = 5;
        int b = 6;
        tree.insert(&a);
        return create_pair(false, tree.contains(&b));
    }, is_eq);

    test<bool>("Insert many then contains", []() {
        BTree::BinaryTree<int> tree;
        int i[] = {0, 1, 2, 3, 4, 5};

        tree.insert(i);
        tree.insert(i + 1);
        tree.insert(i + 2);
        tree.insert(i + 3);
        tree.insert(i + 4);
        tree.insert(i + 5);

        int r = rand() % 5;

        return create_pair(true, tree.contains(&r));
    }, is_eq);

    test<bool>("Insert many then not contains", []() {
        BTree::BinaryTree<int> tree;
        int i[] = {0, 1, 2, 3, 4, 5};

        tree.insert(i);
        tree.insert(i + 1);
        tree.insert(i + 2);
        tree.insert(i + 3);
        tree.insert(i + 4);
        tree.insert(i + 5);

        int r = (rand() % 5) + 6;

        return create_pair(false, tree.contains(&r));
    }, is_eq);
    
    return 0;
}