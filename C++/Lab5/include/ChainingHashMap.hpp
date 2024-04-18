#ifndef CHAINING_HASH_MAP_H
#define CHAINING_HASH_MAP_H

#include <ArrayMap.hpp>
#include <LinkedList.hpp>
#include <HashFunction.hpp>

/// @brief Implementation of a hash map which uses chains to rectify collisions.
/// @param K The key type.
/// @tparam V The value type.
template <class K, class V>
class ChainingHashMap {
private:
    LinkedList<MapRecord<Hashable<K>, V>>* chainArray;
    HashFunction* hashFunction;
    int length;
    int chainCount;
    float maxLoadFactor;

    /// @brief Resize the hash map
    /// @param newChainCount The new chain count
    void resize(int newChainCount) {
        if (newChainCount < 1) throw VALUE_ERROR;

        LinkedList<MapRecord<Hashable<K>, V>>* oldArray = this->chainArray;
        this->chainArray = (LinkedList<MapRecord<Hashable<K>, V>>*) malloc(newChainCount * sizeof(LinkedList<MapRecord<Hashable<K>, V>>));

        int oldChainCount = this->chainCount;
        this->chainCount = newChainCount;
        this->hashFunction = new HashFunction(newChainCount);
        this->length = 0;

        for (int i = 0; i < oldChainCount; i++) {
            for (int a = 0; a < oldArray[i].get_length(); a++) {
                Hashable<K> key = oldArray[i].get_at(a).key;
                this->insert(&key, oldArray[i].get_at(a).value);
            }
        }

    }

    /// @brief Get the chain associated with a certain key
    /// @param key The key to get
    /// @return The chain associated with the given key
    LinkedList<MapRecord<Hashable<K>, V>>* getChain(Hashable<K>* key) {
        return this->chainArray + this->hashFunction->hash(key);
    }

public:
    static const int VALUE_ERROR = 201;
    static const int KEY_ERROR = 202;

    ChainingHashMap(float maxLoadFactor) {
        if (maxLoadFactor <= (1 / 2)) throw VALUE_ERROR;
        this->chainArray = (LinkedList<MapRecord<Hashable<K>, V>>*) malloc(sizeof(LinkedList<MapRecord<Hashable<K>, V>>));
        this->hashFunction = new HashFunction(1);
        this->length = 0;
        this->chainCount = 1;
        this->maxLoadFactor = maxLoadFactor;
    }

    ChainingHashMap() {
        this->chainArray = (LinkedList<MapRecord<Hashable<K>, V>>*) malloc(sizeof(LinkedList<MapRecord<Hashable<K>, V>>));
        this->hashFunction = new HashFunction(1);
        this->length = 0;
        this->chainCount = 1;
        this->maxLoadFactor = 2;
    }

    /// @brief Build a new hash map
    /// @param items The records to insert into the new hash map
    /// @param n The number of items
    /// @param maxLoadFactor The proportion of items to chains at which the table is considered "too full"
    /// @return A new hash map containing the provided items.
    static ChainingHashMap<K, V>* build(MapRecord<Hashable<K>, V>* items, int n, float maxLoadFactor) {
        ChainingHashMap<K, V>* map = new ChainingHashMap<K, V>(maxLoadFactor);

        for (int i = 0; i < n; i++) {
            map->insert(&items[i].key, items[i].value);
        }

        return map;
    }

    int getChainCount() {
        return this->chainCount;
    }

    /// @brief Check if the map contains a certain key
    /// @param key The key to look for
    /// @return true / false
    bool contains(Hashable<K>* key) {
        LinkedList<MapRecord<Hashable<K>, V>>* chain = this->getChain(key);

        for (int i = 0; i < chain->get_length(); i++) {
            if (chain->get_at(i).key == *key) return true;
        }

        return false;
    }

    /// @brief Check if the map is empty or not
    /// @return true / false
    bool isEmpty() {
        return this->length == 0;
    }

    int getLength() {
        return this->length;
    }

    /// @brief Get the value associated with a key
    /// @param key The key
    /// @return The value associated with the given key
    V get(Hashable<K>* key) {
        LinkedList<MapRecord<Hashable<K>, V>>* chain = this->getChain(key);

        for (int i = 0; i < chain->get_length(); i++) {
            if (chain->get_at(i).key == *key) {
                return chain->get_at(i).value;
            }
        }

        throw KEY_ERROR;
    }

    /// @brief Insert an item into the hashmap
    /// @param key The key of the item
    /// @param value The value to insert
    void insert(Hashable<K>* key, V value) {
        LinkedList<MapRecord<Hashable<K>, V>>* chain = this->getChain(key);
        std::cout << "\tGot chain" << std::endl;
        MapRecord<Hashable<K>, V> record(*key, value);
        std::cout << "\tMade record" << std::endl;
        if (chain->contains(record)) {
            std::cout << "\tContains" << std::endl;
            for (int i = 0; i < chain->get_length(); i++) {
                if (chain->get_at(i) == record) {
                    chain->set_at(i, record);
                    return;
                }
            }
        }
        else {
            chain->insert_last({*key, value});
            length++;
        }

        if (length / chainCount > maxLoadFactor) {
            this->resize(chainCount * 2);
        }
    }

    /// @brief Remove an item from the hashmap
    /// @param key The key to remove
    /// @return The item which was associated with the given key
    V remove(Hashable<K>* key) {
        LinkedList<MapRecord<Hashable<K>, V>>* chain = this->getChain(key);

        for (int i = 0; i < chain->get_length(); i++) {
            if (chain->get_at(i).key == *key) {
                length--;
                MapRecord<Hashable<K>, V> r = chain->remove_at(i);
                return r.value;
            }
        }

        throw KEY_ERROR;
    }

    /// @brief Call a function for every record in the hash map
    /// @param f The function to call
    void for_each(void (*f)(int i, MapRecord<Hashable<K>, V>)) {
        int c = 0;
        for (int i = 0; i < chainCount; i++) {
            for (int a = 0; a < chainArray[i].get_length(); a++) {
                f(c, chainArray[i].get_at(a));
                c++;
            }
        }
    }

    /// @brief Call a function for every key in the hash map
    /// @param f The function to call
    void for_each(void (*f)(int i, Hashable<K> key)) {
        int c = 0;
        for (int i = 0; i < chainCount; i++) {
            for (int a = 0; a < chainArray[i].get_length(); a++) {
                f(c, chainArray[i].get_at(a).key);
                c++;
            }
        }
    }
};

#endif