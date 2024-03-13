#ifndef PROBINGHASHMAP_H
#define PROBINGHASHMAP_H

#include <HashFunction.hpp>
#include <stdlib.h>


template <class K, class V>
class ProbingHashMap {
private:
    MapRecord<Hashable<K>, V>** array;
    int size = 0;
    int length = 0;
    float maxLoadFactor;
    HashFunction* hashFunction;

    void resize(int newSize) {
        if (newSize < 1) throw VALUE_ERROR;

        ProbingHashMap<K, V>* map = new ProbingHashMap<K, V>(maxLoadFactor);
        map->array = (MapRecord<Hashable<K>, V>**) malloc(sizeof(MapRecord<Hashable<K>, V>*) * newSize);
        map->size = newSize;
        map->length = 0;

        for (int i = 0; i < size; i++) {
            if (array[i] != nullptr) {
                map->insert(&array[i]->key, array[i]->value);
            }
        }

        *this = *map;
    }

public:
    static const int VALUE_ERROR = 201;
    static const int KEY_ERROR = 202;

    ProbingHashMap(float maxLoadFactor) {
        if (!(1 / 2 < maxLoadFactor && maxLoadFactor <= 1)) throw VALUE_ERROR;

        this->array = (MapRecord<Hashable<K>, V>**) malloc(sizeof(MapRecord<Hashable<K>, V>*));
        this->array[0] = nullptr;
        size = 1;
        this->hashFunction = new HashFunction(1);
        this->maxLoadFactor = maxLoadFactor;
    }

    ProbingHashMap() {
        this->array = (MapRecord<Hashable<K>, V>**) malloc(sizeof(MapRecord<Hashable<K>, V>*));
        this->array[0] = nullptr;
        size = 1;
        this->hashFunction = new HashFunction(1);
        this->maxLoadFactor = 0.8;
    }

    static ProbingHashMap<K, V>* build(MapRecord<Hashable<K>, V>* records, int n, float maxLoadFactor) {
        ProbingHashMap<K, V>* map = new ProbingHashMap<K, V>(maxLoadFactor);
        
        for (int i = 0; i < n; i++) {
            map->insert(&records[i].key, records[i].value);
        }

        return map;
    }

    bool isEmpty() {
        return length == 0;
    }

    int getSize() {
        return size;
    }

    int getLength() {
        return length;
    }

    void optimise() {
        resize(getSize());
    }

    bool contains(Hashable<K>* key) {
        unsigned long long hash = hashFunction->hash(key);
        if (array[hash] != nullptr) {
            if (array[hash]->key == *key) {
                return true;
            }
        }

        for (unsigned long long i = hash + 1; i != hash; i = (i + 1) % size) {
            if (array[i] != nullptr) {
                if (array[i]->key == *key) {
                    return true;
                }
            }
        }

        return false;
    }

    V get(Hashable<K>* key) {
        unsigned long long hash = hashFunction->hash(key);
        if (array[hash] != nullptr) {
            if (array[hash]->key == *key) {
                return array[hash]->value;
            }
        }

        for (unsigned long long i = hash + 1; i != hash; i = (i + 1) % size) {
            if (array[i] != nullptr) {
                if (array[i]->key == *key) {
                    return array[i]->value;
                }
            }
        }

        throw KEY_ERROR;
    }

    void insert(Hashable<K>* key, V value) {
        unsigned long long hash = hashFunction->hash(key);

        if (array[hash] == nullptr) {
            array[hash] = new MapRecord<Hashable<K>, V>(*key, value);
            length++;
            if ((length / size) > maxLoadFactor) resize(size * 2);
            return;
        }
        else if (array[hash]->key == *key) {
            array[hash] = new MapRecord<Hashable<K>, V>(*key, value);
            return;
        }

        for (unsigned long long i = hash + 1; i != hash; i = (i + 1) % size) {
            if (array[i] == nullptr) {
                array[i] = new MapRecord<Hashable<K>, V>(*key, value);
                length++;
                if ((length / size) > maxLoadFactor) resize(size * 2);
                return;
            }
            else if (array[i]->key == *key) {
                array[i] = new MapRecord<Hashable<K>, V>(*key, value);
                return;
            }
        }
    }

    V remove(Hashable<K>* key) {
        unsigned long long hash = hashFunction->hash(key);

        if (array[hash] != nullptr) {
            if (array[hash]->key == *key) {
                V value = array[hash]->value;
                array[hash] = nullptr;
                return value;
            }
        }

        for (unsigned long long i = hash + 1; i != hash; i = (i + 1) % size) {
            if (array[i] != nullptr) {
                if (array[i]->key == *key) {
                    V value = array[i]->value;
                    array[i] = nullptr;
                    return value;
                } 
            }
        }

        throw KEY_ERROR;
    }

    void for_each(void (*f)(int, MapRecord<Hashable<K>, V>)) {
        for (int i = 0; i < size; i++) {
            if (array[i] != nullptr) {
                f(i, *array[i]);
            }
        }
    }

    void for_each(void (*f)(int, Hashable<K>)) {
        for (int i = 0; i < size; i++) {
            if (array[i] != nullptr) {
                f(i, array[i]->key);
            }
        }
    }

    void for_each(void (*f)(int, V)) {
        for (int i = 0; i < size; i++) {
            if (array[i] != nullptr) {
                f(i, array[i]->value);
            }
        }
    }
};

#endif