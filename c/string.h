#pragma once

#include <stddef.h>

inline size_t strlen(const char* buffer)
{
    size_t count = 0;
    while(*buffer != '\0') {
        count++;
        buffer++;
    }
    return count;
}