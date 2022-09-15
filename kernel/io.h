#ifndef IO_H
#define IO_H

#include <stdint.h>

void io_write(uint16_t, uint8_t);
uint8_t io_read(uint16_t);

#endif