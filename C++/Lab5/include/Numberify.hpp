#ifndef NUMBERIFY_H
#define NUMBERIFY_H

#include <stdlib.h>
#include <cstring>

/// @brief Hash a buffer into a single long (8 bytes)
/// @param buffer The buffer to hash
/// @param buffer_size The size of the buffer (in bytes)
/// @return The resulting hash.
unsigned long long to_long(unsigned char* buffer, int buffer_size) {
    // Make sure the size of the buffer is a multiple of 8.
    // I.e. it fits perfectly into a set of longs
    if ((buffer_size % 8) != 0) {
        unsigned char* new_buffer = (unsigned char*) malloc((buffer_size / 8) + 8);
        memcpy(new_buffer, buffer, buffer_size);
        buffer = new_buffer;
        buffer_size = (buffer_size / 8) + 8;
    }

    // XOR all the longs in the buffer against each other to produce a hash.
    unsigned long long* int_buffer = (unsigned long long*) buffer;
    unsigned long long res = 0;
    for (int i = 0; i < (buffer_size / 8); i++) {
        res ^= int_buffer[i];
    }
    
    return res;
};

#endif