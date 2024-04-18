#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <LinkedStack.hpp>
#include <LinkedQueue.hpp>
#include <ChainingHashMap.hpp>
#include <ArrayMap.hpp>
#include <HashFunction.hpp>
#include <LinkedList.hpp>

/// @brief BTree namespace. This is used because some of the name definitions may conflict with parts of other labs.
namespace BinaryTree {
    HashFunction hasher((~0) * -1);

    template <class K, class V>
    class Node {
    public:
        K* key;
        V* value;
        Node<K, V>* left;
        Node<K, V>* right;

        Node(K k, V v) {
            key = (K*) malloc(sizeof(K));
            *key = k;

            value = (V*) malloc(sizeof(V));
            *value = v;

            left = nullptr;
            right = nullptr;
        }

        Node(Node<K, V>& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;
        }

        Node(Node<K, V>&& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;

            n.key = nullptr;
            n.value = nullptr;
            n.left = nullptr;
            n.right = nullptr;
        }

        Node<K, V>& operator=(Node<K, V>& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;
            return *this;
        }

        Node<K, V>&& operator=(Node<K, V>&& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;
            n.key = nullptr;
            n.value = nullptr;
            n.left = nullptr;
            n.right = nullptr;
            return *this;
        }

        ~Node() {
            key = nullptr;
            value = nullptr;
            left = nullptr;
            right = nullptr;
        }

        bool operator>=(Node<K, V> n) {
            unsigned long long hashA = hasher.hash(new Hashable<K>(key));
            unsigned long long hashB = hasher.hash(new Hashable<K>(n.key));

            return hashA >= hashB;
        }

        bool operator<(Node<K, V> n) {
            unsigned long long hashA = hasher.hash(new Hashable<K>(key));
            unsigned long long hashB = hasher.hash(new Hashable<K>(n.key));

            return hashA < hashB;
        }
    };

    /// @brief Binary tree data structure
    /// @param K The type of the key
    /// @param V The type of the value
    template <class K, class V>
    class Tree {
    private:
        Node<K, V>* root;

    public:
        Tree() {
            root = nullptr;
        }

        /// @brief Check if the tree contains a certain key.
        /// @param k The key to search for
        /// @return Whether or not the tree contains the given key
        bool contains(K k) {
            if (root == nullptr) return false;

            LinkedStack<Node<K, V>*> stack;
            stack.push(root);

            while (!stack.is_empty()) {
                std::cout << stack.get_length() << std::endl;
                Node<K, V>* n = stack.pop();
                
                std::cout << "Popped" << std::endl;

                if (*n->key == k) {
                    std::cout << "Is eq" << std::endl;
                    return true;
                }

                std::cout << "Is not eq" << std::endl;

                std::cout << n->left << " " << n->right << std::endl;
                
                if (n->left != nullptr) { 
                    stack.push(n->left);
                    std::cout << "Pushed left" << std::endl;
                }

                if (n->right != nullptr) { 
                    stack.push(n->right);
                    std::cout << "Pushed right" << std::endl;
                }
            }

            return false;
        }

        /// @brief Insert a new node into the tree
        /// @param k The key attached to the new node
        /// @param v The value attached to the new node
        void insert(K k, V v) {
            Node<K, V>* newNode = new Node<K, V>(k, v);

            if (root == nullptr) {
                root = newNode;
                return;
            }

            Node<K, V>* n = root;
            while (n != nullptr) {
                if (*newNode >= *n) {
                    if (n->right == nullptr) {
                        n->right = newNode;
                        return;
                    }
                    else {
                        n = n->right;
                    }
                }
                else {
                    if (n->left == nullptr) {
                        n->left = newNode;
                        return;
                    }
                    else {
                        n = n->left;
                    }
                }
            }
        }

        void depth_for_each(void (*f)(int, K, V)) {
            if (root == nullptr) return;

            LinkedStack<Node<K, V>*> stack;
            stack.push(root);
            int i = 0;

            while (!stack.is_empty()) {
                Node<K, V>* n = stack.pop();
                f(i, *n->key, *n->value);
                stack.push(n->left);
                stack.push(n->right);
                i++;
            }
        }

        void breadth_for_each(void (*f)(int, K, V)) {
            if (root == nullptr) return;

            LinkedQueue<Node<K, V>*> queue;
            queue.push(root);
            int i = 0;

            while (!queue.is_empty()) {
                Node<K, V>* n = queue.pop();
                f(i, *n->key, *n->value);
                queue.push(n->left);
                queue.push(n->right);
                i++;
            }
        }
    };
}

#endif