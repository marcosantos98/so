#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// NULL & UNUSED, Code and Data Segments
#define NUM_SEGMENTS 3

struct GDTEntry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct GDTPtr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

typedef struct GDTEntry GDTEntry;
typedef struct GDTPtr GDTPtr;

extern void gdt_flush(uint32_t);

void gdt_main();
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity);

#endif