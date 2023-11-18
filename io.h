#pragma once

#include <stdint.h>

// Read value of `port` to into `rv` using `in` instruction.
inline static uint8_t ioRead(uint16_t port)
{
    uint8_t rv;
    asm volatile("in %1, %0"
                 : "=a"(rv)
                 : "dN"(port));
    return rv;
}

// Write value `data` to `port` using `out` instrution
inline static void ioWrite(uint16_t port, uint8_t data)
{
    asm volatile("out %1, %0" ::"dN"(port), "a"(data));
}