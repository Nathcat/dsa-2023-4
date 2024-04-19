#include <iostream>
#include <Testing.hpp>
#include <BinaryTree.hpp>
#include <random>
#include <time.h>

#include <HashFunction.hpp>

int main() {
    srand(time(0));

    test<bool>("Contains on empty tree", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* key = "A";
        return create_pair(false, tree.contains(key));
    }, is_eq);

    test<bool>("Insert then contains", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* key = "A";
        tree.insert(key, 5);
        
        return create_pair(true, tree.contains(key));
    }, is_eq);

    test<bool>("Insert then not contains", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* key = "A";
        tree.insert(key, 5);

        return create_pair(false, tree.contains("B"));
    }, is_eq);

    test<bool>("Insert many then contains", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        for (int i = 0; i < 5; i++) {
            tree.insert(*(keys + i), i);
        }

        int r = rand() % 5;
        return create_pair(true, tree.contains(keys[r]));
    }, is_eq);

    test<bool>("Insert many then not contains", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        for (int i = 0; i < 5; i++) {
            tree.insert(*(keys + i), i);
        }

        return create_pair(false, tree.contains("F"));
    }, is_eq);
    
    return 0;
}