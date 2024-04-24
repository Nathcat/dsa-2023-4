#include <iostream>
#include <Testing.hpp>
#include <BinaryTree.hpp>
#include <random>
#include <time.h>
#include <HashFunction.hpp>
#include <InsertionSort.hpp>

template <class K>
class KeyHashPair {
public:
    K* key;
    unsigned long long hash;

    KeyHashPair() {
        key = nullptr;
        hash = 0;
    }

    KeyHashPair(K k, unsigned long long h) {
        key = (K*) malloc(sizeof(K));
        *key = k;
        hash = h;
    }

    KeyHashPair(KeyHashPair<K>& n) {
        key = n.key;
        hash = n.hash;
    }

    KeyHashPair(KeyHashPair<K>&& n) {
        key = n.key;
        hash = n.hash;
        n.key = nullptr;
    }

    ~KeyHashPair() {
        key = nullptr;
    }

    bool operator>(KeyHashPair<K> n) {
        return hash > n.hash;
    }

    bool operator<(KeyHashPair<K> n) {
        return hash < n.hash;
    }

    bool operator<=(KeyHashPair<K> n) {
        return hash <= n.hash;
    }

    bool operator>=(KeyHashPair<K> n) {
        return hash >= n.hash;
    }

    bool operator==(KeyHashPair<K> n) {
        return hash == n.hash;
    }

    KeyHashPair<K>& operator=(KeyHashPair<K>& n) {
        key = n.key;
        hash = n.hash;
        return *this;
    }

    KeyHashPair<K>&& operator=(KeyHashPair<K>&& n) {
        key = n.key;
        hash = n.hash;
        n.key = nullptr;
        return *this;
    }
};

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
    
    /*
    test<int>("Get height", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        unsigned long long* hashes = (unsigned long long*) malloc(sizeof(unsigned long long) * 5);
        
        for (int i = 0; i < 5; i++) {
            tree.insert(*(keys + i), i);
            hashes[i] = BinaryTree::hasher.hash(keys + i);
            printf("Inserted %s with hash %lld.\n", keys[i], hashes[i]);
        }

        int expecting;
        std::cout << "What height should we expect? > ";
        std::cin >> expecting;
        std::cout << std::endl;

        return create_pair(expecting, tree.get_height());
    }, is_eq);*/

    test<int>("Get", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        
        for (int i = 0; i < 5; i++) {
            tree.insert(keys[i], i);
        }

        int r = rand() % 5;
        return create_pair(r, tree.get(keys[r]));
    }, is_eq);

    test<int>("Remove", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        //KeyHashPair<const char*>* pairs = (KeyHashPair<const char*>*) malloc(sizeof(KeyHashPair<const char>*) * 5);

        for (int i = 0; i < 5; i++) {
            tree.insert(keys[i], i);
        }



        int r = rand() % 5;
        return create_pair(r, tree.remove(keys[r]));
    }, is_eq);

    test<int>("Remove then get", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        
        for (int i = 0; i < 5; i++) {
            tree.insert(keys[i], i);
        }

        int r = rand() % 5;
        tree.remove(keys[r]);

        try {
            tree.get(keys[r]);
        } catch (int err) {
            printf("Also allow 202 in cases where the node removed was the root node.\n");
            return create_pair(BinaryTree::Tree<const char*, int>::DOES_NOT_CONTAIN, err);
        }

        return create_pair(-1, 0);
    }, is_eq);

    test<const char*>("Get minimum key", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        KeyHashPair<const char*>* pairs = (KeyHashPair<const char*>*) malloc(sizeof(KeyHashPair<const char*>) * 5);

        for (int i = 0; i < 5; i++) {
            tree.insert(keys[i], i);
            KeyHashPair<const char*> p(keys[i], BinaryTree::hasher.hash(keys + i));
            pairs[i] = p;
        }

        insertion_sort(pairs, 5);

        return create_pair(*pairs[0].key, tree.get_minimum_key());
    }, is_eq);

    test<const char*>("Get maximum key", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        KeyHashPair<const char*>* pairs = (KeyHashPair<const char*>*) malloc(sizeof(KeyHashPair<const char*>) * 5);

        for (int i = 0; i < 5; i++) {
            tree.insert(keys[i], i);
            KeyHashPair<const char*> p(keys[i], BinaryTree::hasher.hash(keys + i));
            pairs[i] = p;
        }

        insertion_sort(pairs, 5);

        return create_pair(*pairs[4].key, tree.get_maximum_key());
    }, is_eq);

    test<const char*>("Get next key", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        KeyHashPair<const char*>* pairs = (KeyHashPair<const char*>*) malloc(sizeof(KeyHashPair<const char*>) * 5);

        for (int i = 0; i < 5; i++) {
            pairs[i].key = keys + i;
            pairs[i].hash = BinaryTree::hasher.hash(keys + i);
            
            tree.insert(keys[i], i);
            KeyHashPair<const char*> p(keys[i], BinaryTree::hasher.hash(keys + i));
        }

        insertion_sort(pairs, 5);

        int r = rand() % 3;
        return create_pair(*pairs[r + 1].key, tree.get_next_key(*pairs[r].key));
    }, is_eq);

    test<int>("Get next key edge case", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        KeyHashPair<const char*>* pairs = (KeyHashPair<const char*>*) malloc(sizeof(KeyHashPair<const char*>) * 5);

        for (int i = 0; i < 5; i++) {
            pairs[i].key = keys + i;
            pairs[i].hash = BinaryTree::hasher.hash(keys + i);

            tree.insert(keys[i], i);
            KeyHashPair<const char*> p(keys[i], BinaryTree::hasher.hash(keys + i));
        }

        insertion_sort(pairs, 5);
    
        try {
            tree.get_next_key(*pairs[4].key);
        } catch (int err) {
            return create_pair(201, err);  // DOES_NOT_CONTAIN
        }
        return create_pair(-1, 0);
    }, is_eq);

    test<const char*>("Get previous key", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        KeyHashPair<const char*>* pairs = (KeyHashPair<const char*>*) malloc(sizeof(KeyHashPair<const char*>) * 5);

        for (int i = 0; i < 5; i++) {
            pairs[i].key = keys + i;
            pairs[i].hash = BinaryTree::hasher.hash(keys + i);
            
            tree.insert(keys[i], i);
            KeyHashPair<const char*> p(keys[i], BinaryTree::hasher.hash(keys + i));
        }

        insertion_sort(pairs, 5);

        int r = (rand() % 4) + 1;
        return create_pair(*pairs[r - 1].key, tree.get_previous_key(*pairs[r].key));
    }, is_eq);

    test<int>("Get previous key edge case", []() {
        BinaryTree::Tree<const char*, int> tree;

        const char* keys[] = {"A", "B", "C", "D", "E"};
        KeyHashPair<const char*>* pairs = (KeyHashPair<const char*>*) malloc(sizeof(KeyHashPair<const char*>) * 5);

        for (int i = 0; i < 5; i++) {
            pairs[i].key = keys + i;
            pairs[i].hash = BinaryTree::hasher.hash(keys + i);

            tree.insert(keys[i], i);
            KeyHashPair<const char*> p(keys[i], BinaryTree::hasher.hash(keys + i));
        }

        insertion_sort(pairs, 5);
    
        try {
            tree.get_previous_key(*pairs[0].key);
        } catch (int err) {
            return create_pair(201, err);  // DOES_NOT_CONTAIN
        }
        return create_pair(-1, 0);
    }, is_eq);
    
    return 0;
}