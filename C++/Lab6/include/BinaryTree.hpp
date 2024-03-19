#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <LinkedStack.hpp>
#include <LinkedQueue.hpp>
#include <ChainingHashMap.hpp>

/// @brief BTree namespace. This is used because some of the name definitions may conflict with parts of other labs.
namespace BTree {
    template <class T>
    class Node {
    public:
        T* data;
        Node<T>* left;
        Node<T>* right;

        Node() {
            data = nullptr;
            left = nullptr;
            right = nullptr;
        }

        Node(T* data) {
            this->data = data;
            left = nullptr;
            right = nullptr;
        }

        Node(T* data, Node<T>* left, Node<T>* right) {
            this->data = data;
            this->left = left;
            this->right = right;
        }

        Node(Node<T>& other) {
            this->data = other.data;
            this->left = other.left;
            this->right = other.right;
        }

        Node(Node<T>&& other) {
            this->data = other.data;
            this->left = other.left;
            this->right = other.right;

            other.data = nullptr;
            other.left = nullptr;
            other.right = nullptr;
        }

        ~Node() {
            this->data = nullptr;
            this->left = nullptr;
            this->right = nullptr;
        }

        Node<T>& operator=(Node<T>& other) {
            this->data = other.data;
            this->left = other.left;
            this->right = other.right;

            return *this;
        }

        Node<T>&& operator=(Node<T>&& other) {
            this->data = other.data;
            this->left = other.left;
            this->right = other.right;

            other.data = nullptr;
            other.left = nullptr;
            other.right = nullptr;

            return *this;
        }

        bool operator==(Node<T> other) {
            return *other.data == *this->data;
        }

        bool operator!=(Node<T> other) {
            return !(*other.data == *this->data);
        }

        bool operator>(Node<T> other) {
            return *this->data > *other.data;
        }

        bool operator<(Node<T> other) {
            return *this->data < *other.data;
        }
    };

    template <class T>
    class BinaryTree {
    private:
        Node<T>* root;

    public:
        BinaryTree() {
            root = nullptr;
        }

        BinaryTree(T* rootData) {
            root = new Node<T>(rootData);
        }

        BinaryTree(Node<T>* root) {
            this->root = root;
        }

        BinaryTree(BinaryTree<T>& t) {
            this->root = t.root;
        }

        BinaryTree(BinaryTree<T>&& t) {
            this->root = t.root;
            delete t.root;
        }

        ~BinaryTree() {
            delete root;
        }

        BinaryTree<T>& operator=(BinaryTree<T>& t) {
            this->root = t.root;
            return *this;
        }

        BinaryTree<T>&& operator=(BinaryTree<T>&& t) {
            this->root = t.root;
            delete t.root;
            return *this;
        }

        bool contains(T* v) {
            Node<T>* n = new Node<T>(v);
            Node<T>* current_node = root;

            while (current_node != nullptr && *current_node != *n) {
                if (*n > *current_node) {
                    current_node = current_node->right;
                }
                else {
                    current_node = current_node->left;
                }
            }

            return current_node != nullptr;
        }

        void insert(T* data) {
            // Please end my suffering, this method is gonna kill me
            // I stg.

            Node<T>* n = new Node<T>(data);

            if (root == nullptr) {
                root = n;
                return;
            }

            Node<T>* current_node = root;
            while (current_node != nullptr) {
                if (*n > *current_node) {
                    if (current_node->right == nullptr) {
                        current_node->right = n;
                        return;
                    }
                    else {
                        current_node = current_node->right;
                    }
                }
                else if (*n < *current_node) {
                    if (current_node->left == nullptr) {
                        current_node->left = n;
                        return;
                    }
                    else {
                        current_node = current_node->left;
                    }
                }
                else {
                    return;
                }
            }
        }

        BinaryTree<T>* remove_left() {
            BinaryTree<T>* left = left_subtree();
            root->left = nullptr;
            return left;
        }

        BinaryTree<T>* remove_right() {
            BinaryTree<T>* right = right_subtree();
            root->right = nullptr;
            return right;
        }

        BinaryTree<T>* left_subtree() {
            return new BinaryTree<T>(root->left);
        }

        BinaryTree<T>* right_subtree() {
            return new BinaryTree<T>(root->right);
        }

        void depth_for_each(void (*f)(int, T)) {
            LinkedStack<Node<T>*> stack;
            ChainingHashMap<T, bool> discovered;
            int i = 0;
            f(i, *root->data); i++;

            stack.push(root);
            discovered.insert(new Hashable<T>(root->data), true);

            while (!stack.is_empty()) {
                Node<T>* current = *(stack.peek());

                if (current->left != nullptr && !discovered.contains(new Hashable<T>(current->left->data))) {
                    f(i, *current->left->data); i++;
                    stack.push(current->left);
                    discovered.insert(new Hashable<T>(current->left->data), true);
                }
                
                if (current->right != nullptr && !discovered.contains(new Hashable<T>(current->right->data))) {
                    f(i, *current->right->data); i++;
                    stack.push(current->right);
                    discovered.insert(new Hashable<T>(current->right->data), true);
                }

                if (current->left == nullptr && current->right == nullptr) {
                    Node<T>** out;
                    if (!stack.pop(&out)) {
                        exit(-1);
                    }
                }
            }
        }

        void breadth_for_each(void (*f)(int, T)) {
            LinkedQueue<Node<T>*> queue;
            ChainingHashMap<T, bool> discovered;
            int i = 0;
            f(i, root->data); i++;

            queue.push(root);
            discovered.insert(new Hashable<T>(&root->data), true);

            while (!queue.is_empty()) {
                Node<T>* current = *(queue.peek());

                if (current->left != nullptr && !discovered.contains(new Hashable<T>(&current->left->data))) {
                    f(i, *current->left->data); i++;
                    queue.push(current->left);
                    discovered.insert(new Hashable<T>(&current->left->data));
                }

                if (current->right != nullptr && !discovered.contains(new Hashable<T>(&current->right->data))) {
                    f(i, *current->right->data); i++;
                    queue.push(current->right);
                    discovered.insert(new Hashable<T>(&current->right->data));
                }

                if (current->left == nullptr && current->right == nullptr) {
                    Node<T>** out;
                    if (!queue.pop(&out)) {
                        exit(-1);
                    }
                }
            }
        }
    };
}

#endif