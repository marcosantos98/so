#pragma once

#include <stdint.h>
#include <stddef.h>

#define PACKED(n) __attribute__ ((packed)) n

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;