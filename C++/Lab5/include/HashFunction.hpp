#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <cstdlib>
#include <ctime>
#include <Numberify.hpp>
#include <cstring>
#include <iostream>
#include <stdio.h>

#define PRIME 2147483647

/// @brief Classes should extend this class and implement its method to allow the class to be hashed by the algorithm implemented here
template <class T> 
class Hashable {
    public:

    T* data;

    Hashable() {
        this->data = nullptr;
    }

    Hashable(T* pD) {
        this->data = pD;
    }

    /// @brief Transform this object into an unsigned char buffer
    /// @param buffer Pointer to assign the buffer to
    /// @return The size of the buffer
    virtual int to_char_buffer(unsigned char** buffer) { return 0; };

    virtual bool operator==(Hashable<T>& other) {
        return false;
    }

    static Hashable<T> create(T* d) {
        Hashable<T> h(d);
        return h;
    }

    /// @brief Copy constructor
    /// @param other The object to copy
    Hashable(Hashable<T>& other) {
        this->data = other.data;
    }

    /// @brief Copy assignment
    /// @param other The object to copy
    /// @return The copied object
    Hashable<T>& operator=(Hashable<T>& other) {
        this->data = other.data;
        return *this;
    }

    /// @brief Move constructor
    /// @param other The object to delete once copied
    Hashable(Hashable<T>&& other) {
        this->data = other.data;
        other.data = nullptr;
    }

    /// @brief Move assignment
    /// @param other The object to delete once copied
    /// @return The copied object
    Hashable<T>&& operator=(Hashable<T>&& other) {
        this->data = other.data;
        other.data = nullptr;
        return *this;
    }
};

//
//  Basic hashable template implementations
//
template<>
int Hashable<int>::to_char_buffer(unsigned char** buffer) {
    *buffer = (unsigned char*) data;
    return sizeof(int);
}

template<>
bool Hashable<int>::operator==(Hashable<int>& other) {
    return *data == *(other.data);
}

template<>
int Hashable<const char*>::to_char_buffer(unsigned char** buffer) {
    *buffer = (unsigned char*) *data;
    return strlen(*data);
}

template<>
bool Hashable<const char*>::operator==(Hashable<const char*>& other) {
    return strcmp(*data, *(other.data)) == 0;
}

//
//  HashFunction
//

class HashFunction {
public:
    int a, b, size;

public:
    static const int VALUE_ERROR = 201;

    HashFunction(int size) {
        srand(time(0));
        
        if (size < 1) throw VALUE_ERROR;

        this->a = (rand() + 1) % (PRIME - 1);
        this->b = rand() % (PRIME - 1);
        this->size = size;
    }

    /// @brief Compare two hashable objects
    /// @tparam T The type contained by the hashables
    /// @param a Hashable 1
    /// @param b Hashable 2
    /// @return 0 if a == b, 1 if a > b, -1 if a < b.
    template<class T>
    int cmp(Hashable<T>* a, Hashable<T>* b) {
        unsigned long long aH = this->hash(a);
        unsigned long long bH = this->hash(b);

        if (aH == bH) return 0;
        else if (aH > bH) return 1;
        else return -1;
    }
 
    template <class T>
    unsigned long long hash(Hashable<T>* h) {
        unsigned char* buffer;
        int buffer_size = h->to_char_buffer(&buffer);
        unsigned long long subhash = to_long(buffer, buffer_size);

        return ((((a * subhash) + b) % PRIME) % size);
    }

    unsigned long long hash(int* v) {
        return this->hash(new Hashable<int>(v));
    }

    unsigned long long hash(const char** str) {
        return this->hash(new Hashable<const char*>(str));
    }
};

#endif