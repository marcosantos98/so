#include "io.h"

uint8_t io_read(uint16_t port)
{
    uint8_t rv;
    asm volatile("in %1, %0"
                 : "=a"(rv)
                 : "dN"(port));
    return rv;
}

void io_write(uint16_t port, uint8_t data)
{
    asm volatile("out %1, %0"
                 :
                 : "dN"(port), "a"(data));
}