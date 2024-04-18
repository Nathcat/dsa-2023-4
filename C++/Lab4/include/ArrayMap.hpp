#ifndef ARRAY_MAP_H
#define ARRAY_MAP_H

#include <StaticArrayList.hpp>
#include <BinarySearch.hpp>

template <class K, class V>
class MapRecord {
public:
    K key;
    V value;

    MapRecord() {
        /*K* pK = (K*) malloc(sizeof(K));
        V* pV = (V*) malloc(sizeof(V));

        key = *pK;
        value = *pV;*/
    }

    MapRecord(K key, V value) {
        this->key = key;
        this->value = value;
    }

    bool operator>(MapRecord<K, V>& other) {
        return this->key > other.key;
    }

    bool operator<(MapRecord<K, V>& other) {
        return this->key < other.key;
    }

    bool operator==(MapRecord<K, V>& other) {
        return this->key == other.key;
    }

    bool operator!=(MapRecord<K, V>& other) {
        return !(this->key == other.key);
    }
};

template <class K, class V>
class ArrayMap {
private:
    StaticArrayList<MapRecord<K, V>>* list;

public:
    const static int KEY_ERROR = 201;

    ArrayMap() {
        this->list = new StaticArrayList<MapRecord<K, V>>();
    }

    /// @brief Build a new map from an existing array of records
    /// @param records The array of records
    /// @param n The number of records
    /// @return A new array map containing the provided records
    static ArrayMap<K, V>* build(MapRecord<K, V>* records, int n) {
        ArrayMap<K, V>* map = new ArrayMap<K, V>();

        for (int i = 0; i < n; i++) {
            map->insert(records[i].key, records[i].value);
        }

        return map;
    }

    /// @brief Check if the map contains a certain key
    /// @param key The key to search for
    /// @return true / false
    int contains(K key) {
        for (int i = 0; i < this->list->get_length(); i++) {
            if (this->list->get_at(i).key == key) return 1;
        }

        return 0;
    }

    /// @brief Check if the map is empty
    /// @return true / false
    int is_empty() {
        return this->list->get_length() == 0;
    }

    /// @brief Get the number of records in the map
    /// @return The number of records in the map
    int get_length() {
        return this->list->get_length();
    }

    /// @brief Get the value attached to a certain key
    /// @param key The key
    /// @return The value attached to the key
    /// @throws KEY_ERROR
    V get(K key) {
        for (int i = 0; i < this->get_length(); i++) {
            if (this->list->get_at(i).key == key) return this->list->get_at(i).value;
        }

        throw KEY_ERROR;
    }

    /// @brief Insert a record into the map
    /// @param key The key
    /// @param value The value
    void insert(K key, V value) {
        MapRecord<K, V> new_record(key, value);
        this->list->insert_last(new_record);
    }

    /// @brief Remove a record from the map
    /// @param key The key to remove
    /// @return The value attached to the key
    /// @throws KEY_ERROR
    V remove(K key) {
        for (int i = 0; i < this->get_length(); i++) {
            if (this->list->get_at(i).key == key) return this->list->remove_at(i).value;
        }

        throw KEY_ERROR;
    }

    /// @brief Call a function for each record in the map
    /// @param f The function to call
    void for_each(void (*f)(int, MapRecord<K, V>)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, this->list->get_at(i));
        }
    }

    /// @brief Call a function for every key in the map
    /// @param f The function to call
    void for_each_keys(void (*f)(int, K)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, this->list->get_at(i).key);
        }
    }

    /// @brief Call a function for every value in the map
    /// @param f The function to call
    void for_each_values(void (*f)(int, V)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, this->list->get_at(i).value);
        }
    }
};

template <class K, class V>
class SortedArrayMap {
private:
    StaticArrayList<MapRecord<K, V>>* list;

public:
    static const int KEY_ERROR = 201;

    SortedArrayMap() {
        std::cout << "Const" << std::endl;
        this->list = new StaticArrayList<MapRecord<K, V>>();
    }

    /// @brief Build a new map from an existing array of records
    /// @param records The array of records
    /// @param n The number of records
    /// @return A new map containing all the provided records
    static SortedArrayMap<K, V>* build(MapRecord<K, V>* records, int n) {
        SortedArrayMap<K, V>* map = new SortedArrayMap<K, V>();

        for (int i = 0; i < n; i++) {
            map->insert(records[i].key, records[i].value);
        }

        return map;
    }

    /// @brief Check if the map contains a certain key
    /// @param key 
    /// @return true / false
    int contains(K key) {
        V* v = (V*) malloc(sizeof(V));
        MapRecord<K, V> tmp_record(key, *v);
        return binary_search<MapRecord<K, V>>(tmp_record, this->list->get_internal_array(), this->get_length()) != -1;
    }

    /// @brief Check if the map is empty
    /// @return true / false
    int is_empty() {
        return this->list->get_length() == 0;
    }

    /// @brief Get the number of records in the map
    /// @return The number of records in the map
    int get_length() {
        return this->list->get_length();
    }

    /// @brief Get the value associated with a certain key
    /// @param key The key to look for
    /// @return The value associated with the provided key
    V get(K key) {
        V* v = (V*) malloc(sizeof(V));
        MapRecord<K, V> tmp_record(key, *v);
        int res = binary_search<MapRecord<K, V>>(tmp_record, this->list->get_internal_array(), this->get_length()) != -1;
        if (res == -1) throw KEY_ERROR;

        return this->list->get_at(res).value;
    }

    /// @brief Insert a new key / value pair to the map
    /// @param key The key
    /// @param value The value
    void insert(K key, V value) {
        this->list->insert_last({key, value});
        std::cout << "Inserted" << std::endl;
        this->list = StaticArrayList<MapRecord<K, V>>::build(merge_sort(this->list->get_internal_array(), this->get_length()).array, this->get_length());
        std::cout << "Sorted" << std::endl;
    }

    /// @brief Remove a record from the map
    /// @param key The key to remove
    /// @return The value which was associated with the removed key
    V remove(K key) {
        V* v = (V*) malloc(sizeof(V));
        MapRecord<K, V> tmp_record(key, *v);
        int res = binary_search<MapRecord<K, V>>(tmp_record, this->list->get_internal_array(), this->get_length()) != -1;
        if (res == -1) throw KEY_ERROR;

        return this->list->remove_at(res).value;
    }

    /// @brief Call a function for each record in the map
    /// @param f The function to call
    void for_each(void (*f)(int, MapRecord<K, V>)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, this->list->get_at(i));
        }
    }
    
    /// @brief Call a function for every key in the map
    /// @param f The function to call
    void for_each_keys(void (*f)(int, K)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, this->list->get_at(i).key);
        }
    }

    /// @brief Call a function for every value in the map
    /// @param f The function to call
    void for_each_values(void (*f)(int, V)) {
        for (int i = 0; i < this->get_length(); i++) {
            f(i, this->list->get_at(i).value);
        }
    }
};

#endif