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
    HashFunction hasher(100);

    template <class K, class V>
    class Node {
    public:
        K* key;
        V* value;
        Node<K, V>* left;
        Node<K, V>* right;
        Node<K, V>* parent;

        Node(K k) {
            key = (K*) malloc(sizeof(K));
            *key = k;

            value = nullptr;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        Node(K k, V v) {
            key = (K*) malloc(sizeof(K));
            *key = k;

            value = (V*) malloc(sizeof(V));
            *value = v;

            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        Node(Node<K, V>& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;
            this->parent = n.parent;
        }

        Node(Node<K, V>&& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;
            this->parent = n.parent;

            n.key = nullptr;
            n.value = nullptr;
            n.left = nullptr;
            n.right = nullptr;
            n.parent = nullptr;

            if (parent->left == &n) parent->left = this;
            if (parent->right == &n) parent->right = this;
        }

        Node<K, V>& operator=(Node<K, V>& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;
            this->parent = n.parent;
            return *this;
        }

        Node<K, V>&& operator=(Node<K, V>&& n) {
            this->key = n.key;
            this->value = n.value;
            this->left = n.left;
            this->right = n.right;
            this->parent = n.parent;
            n.key = nullptr;
            n.value = nullptr;
            n.left = nullptr;
            n.right = nullptr;
            n.parent = nullptr;
            if (parent->left == &n) parent->left = this;
            if (parent->right == &n) parent->right = this;
            return *this;
        }

        ~Node() {
            key = nullptr;
            value = nullptr;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        bool operator>(Node<K, V> n) {
            unsigned long long hashA = hasher.hash(new Hashable<K>(key));
            unsigned long long hashB = hasher.hash(new Hashable<K>(n.key));

            return hashA >= hashB;
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

        bool operator<=(Node<K, V> n) {
            unsigned long long hashA = hasher.hash(new Hashable<K>(key));
            unsigned long long hashB = hasher.hash(new Hashable<K>(n.key));

            return hashA <= hashB;
        }

        bool operator==(Node<K, V> n) {
            unsigned long long hashA = hasher.hash(new Hashable<K>(key));
            unsigned long long hashB = hasher.hash(new Hashable<K>(n.key));

            return hashA == hashB;
        }
    };

    /// @brief Binary tree data structure
    /// @param K The type of the key
    /// @param V The type of the value
    template <class K, class V>
    class Tree {
    private:
        Node<K, V>* root;
        int length;

        void recount_length() {
            length = 0;
            LinkedStack<Node<K, V>*> stack;
            stack.push(root);
            while (!stack.is_empty()) {
                Node<K, V>* N = stack.pop();
                if (N->left != nullptr) stack.push(N->left);
                if (N->right != nullptr) stack.push(N->right);
                length++;
            }
        }

    public:
        static const int DOES_NOT_CONTAIN = 201;
        static const int TREE_IS_EMPTY = 202;

        Tree() {
            root = nullptr;
            length = 0;
        }

        Tree(Node<K, V>* n) {
            root = n;

            recount_length();
        }

        Tree(Tree<K, V>& t) {
            root = t.root;
            length = t.length;
        }

        Tree(Tree<K, V>&& t) {
            root = t.root;
            length = t.length;
            t.root = nullptr;
        }

        Tree<K, V>& operator=(Tree<K, V>& t) {
            root = t.root;
            length = t.length;
            return *this;
        }

        Tree<K, V>&& operator=(Tree<K, V>&& t) {
            root = t.root;
            length = t.length;
            t.root = nullptr;
            return *this;
        }

        ~Tree() {
            root = nullptr;
        }

        Node<K, V>* get_root() {
            return root;
        }

        /// @brief Check if the tree contains a certain key.
        /// @param k The key to search for
        /// @return Whether or not the tree contains the given key
        bool contains(K k) {
            if (root == nullptr) return false;

            Node<K, V> Nk(k);

            LinkedStack<Node<K, V>*> stack;
            stack.push(root);

            while (!stack.is_empty()) {
                Node<K, V>* n = stack.pop();
                
                if (*n == Nk) {
                    return true;
                }

                if (n->left != nullptr) { 
                    stack.push(n->left);
                }

                if (n->right != nullptr) { 
                    stack.push(n->right);
                }
            }

            return false;
        }

        /// @brief Check if the tree is empty
        /// @return Whether or not the tree is empty
        bool is_empty() {
            return root == nullptr;
        }

        /// @brief Get the number of items in the tree
        /// @return The number of items in the tree
        int get_length() {
            return length;
        }

        /// @brief Get the subtree whose root node is the left node of this tree's root node
        /// @return The left subtree of this tree
        Tree<K, V>* get_left_subtree() {
            if (root->left == nullptr) return new Tree<K, V>();
            return new Tree<K, V>(root->left);
        }

        /// @brief Get the subtree whose root node is the right node of this tree's root node
        /// @return The right subtree of this tree
        Tree<K, V>* get_right_subtree() {
            if (root->right == nullptr) return new Tree<K, V>();
            return new Tree<K, V>(root->right);
        }

        /// @brief Get the number of levels below the root of this tree
        /// @return The height of the tree
        int get_height() {
            if (is_empty()) return -1;
            if (length == 1) return 0;

            int lHeight = get_left_subtree()->get_height();
            int rHeight = get_right_subtree()->get_height();

            if (lHeight >= rHeight) return lHeight + 1;
            else return rHeight + 1;
        }

        /// @brief Insert a new node into the tree
        /// @param k The key attached to the new node
        /// @param v The value attached to the new node
        void insert(K k, V v) {
            Node<K, V>* newNode = new Node<K, V>(k, v);

            if (root == nullptr) {
                root = newNode;
                length++;
                return;
            }

            Node<K, V>* n = root;
            while (n != nullptr) {
                if (*newNode >= *n) {
                    if (n->right == nullptr) {
                        newNode->parent = n;
                        n->right = newNode;
                        length++;
                        return;
                    }
                    else {
                        n = n->right;
                    }
                }
                else {
                    if (n->left == nullptr) {
                        newNode->parent = n;
                        n->left = newNode;
                        length++;
                        return;
                    }
                    else {
                        n = n->left;
                    }
                }
            }
        }

        /// @brief Get the value attached to a certain key.
        /// @param k The key to search for
        /// @return The value attached to the key
        /// @throws DOES_NOT_CONTAIN and TREE_IS_EMPTY
        V get(K k) {
            if (root == nullptr) throw TREE_IS_EMPTY;
            
            Node<K, V> Nk(k);
            if (*root == Nk) return *root->value;

            LinkedStack<Node<K, V>*> stack;
            stack.push(root);

            while (!stack.is_empty()) {
                Node<K, V>* n = stack.pop();

                if (*n == Nk) return *n->value;

                if (n->left != nullptr && Nk < *n) stack.push(n->left);
                if (n->right != nullptr && Nk > *n) stack.push(n->right);
            }

            throw DOES_NOT_CONTAIN;
        }

        /// @brief Remove a key and its subtree of keys from the tree
        /// @param k The key to remove
        /// @return The value attached to the removed key
        /// @throws DOES_NOT_CONTAIN and TREE_IS_EMPTY
        V remove(K k) {
            if (root == nullptr) throw TREE_IS_EMPTY;
            
            Node<K, V> Nk(k);
            LinkedStack<Node<K, V>*> stack;
            stack.push(root);
            while (!stack.is_empty()) {
                Node<K, V>* n = stack.pop();

                if (*n == Nk) {
                    V v = *n->value;
                    if (n->parent == nullptr) {
                        root = nullptr;
                        length = 0;
                        return v;
                    }

                    if (n->parent->left == n) n->parent->left = nullptr;
                    if (n->parent->right == n) n->parent->right = nullptr;

                    recount_length();
                    return v;
                }

                if (n->left != nullptr && Nk < *n) stack.push(n->left);
                if (n->right != nullptr && Nk > *n) stack.push(n->right);
            }

            throw DOES_NOT_CONTAIN;
        }

        /// @brief Get the smallest key in the tree
        /// @return The smallest key in the tree
        /// @throws TREE_IS_EMPTY
        K get_minimum_key() {
            if (root == nullptr) throw TREE_IS_EMPTY;

            Node<K, V>* n = root;
            while (n->left != nullptr) {
                n = n->left;
            }

            return *n->key;
        }

        /// @brief Get the largest key in the tree
        /// @return The largest key in the tree
        /// @throws TREE_IS_EMPTY
        K get_maximum_key() {
            if (root == nullptr) throw TREE_IS_EMPTY;

            Node<K, V>* n = root;
            while (n->right != nullptr) {
                n = n->right;
            }

            return *n->key;
        }

        /// @brief Get the next largest key in the tree
        /// @param k The maximum key such that k < k_next
        /// @return k_next
        /// @throws DOES_NOT_CONTAIN and TREE_IS_EMPTY
        K get_next_key(K k) {
            if (root == nullptr) throw TREE_IS_EMPTY;

            Node<K, V> Nk(k);
            LinkedStack<Node<K, V>*> stack;
            stack.push(root);
            while (!stack.is_empty()) {
                Node<K, V>* n = stack.pop();
                
                if (*n == Nk) {
                    if (n->right != nullptr) {
                        n = n->right;
                        while (n->left != nullptr) {
                            n = n->left;
                        }

                        return *n->key;
                    }

                    Node<K, V>* asc = n->parent;
                    while (asc != nullptr && n != asc->left) {
                        n = asc;
                        asc = asc->parent;
                    }
                       
                    if (asc == nullptr) throw DOES_NOT_CONTAIN;
                    
                    return *asc->key;                
                }
                
                if (n->left != nullptr && Nk < *n) stack.push(n->left);
                if (n->right != nullptr && Nk > *n) stack.push(n->right);
            }

            throw DOES_NOT_CONTAIN;
        }

        /// @brief Get the previous key from the given key
        /// @param k The smallest key such that K-prev < k
        /// @return K-prev
        K get_previous_key(K k) {
            if (root == nullptr) throw TREE_IS_EMPTY;

            Node<K, V> Nk(k);
            LinkedStack<Node<K, V>*> stack;
            stack.push(root);
            while (!stack.is_empty()) {
                Node<K, V>* n = stack.pop();

                if (*n == Nk) {
                    if (n->left != nullptr) {
                        n = n->left;
                        while (n->right != nullptr) {
                            n = n->right;
                        }

                        return *n->key;
                    }

                    Node<K, V>* asc = n->parent;
                    while (asc != nullptr && n != asc->right) {
                        n = asc;
                        asc = asc->parent;
                    }

                    if (asc == nullptr) throw DOES_NOT_CONTAIN;

                    return *asc->key;
                }

                if (n->left != nullptr && Nk < *n) stack.push(n->left);
                if (n->right != nullptr && Nk > *n) stack.push(n->right);
            }

            throw DOES_NOT_CONTAIN;
        }

        void depth_for_each(void (*f)(int, K, V)) {
            if (root == nullptr) return;

            LinkedStack<Node<K, V>*> stack;
            stack.push(root);
            int i = 0;

            while (!stack.is_empty()) {
                Node<K, V>* n = stack.pop();
                f(i, *n->key, *n->value);
                
                if (n->left != nullptr) stack.push(n->left);
                if (n->right != nullptr) stack.push(n->right);
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
                if (n->left != nullptr) queue.push(n->left);
                if (n->right != nullptr) queue.push(n->right);
                i++;
            }
        }
    };
}

#endif