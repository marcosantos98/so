#pragma once

#include "nice.h"

// Read value of `port` to into `rv` using `in` instruction.
inline static u8 ioRead(u16 port)
{
    u8 rv;
    asm volatile("in %1, %0"
                 : "=a"(rv)
                 : "dN"(port));
    return rv;
}

// Write value `data` to `port` using `out` instrution
inline static void ioWrite(u16 port, u8 data)
{
    asm volatile("out %1, %0" ::"dN"(port), "a"(data));
}