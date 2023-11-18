#include "gdt.h"

// Currently 3, but later one we will add the User Space segments
// NULL, CODE, DATA
#define NUM_SEGMENTS 3
#define NULL_SEGMENT 0
#define CODE_SEGMENT 0
#define DATA_SEGMENT 0

#include "nice.h"

typedef struct {
    u16 limit;
    u32 base;
} PACKED(GlobalDescriptorTable);

typedef struct 
{
    u16 limit;
    u16 base;
    u8 _base;
    u8 pptf; // present, privilege, type, flags
    u8 other; 
    u8 __base;
} PACKED(GDTSegment);

void gdtInit()
{
    GDTSegment segs[NUM_SEGMENTS] = {0};

    GlobalDescriptorTable gdt;
    gdt.limit = sizeof(GDTSegment) * 3 - 1;
    gdt.base = (u32)&segs;

    // Null segment
    segs[NULL_SEGMENT].limit = 0x0;
    segs[NULL_SEGMENT].base = 0x0;
    segs[NULL_SEGMENT]._base = 0x0;
    segs[NULL_SEGMENT].pptf = 0x0;
    segs[NULL_SEGMENT].other = 0x0;
    segs[NULL_SEGMENT].__base = 0x0;

    // Code Segment
    segs[CODE_SEGMENT].limit = 0xFFFF;
    segs[CODE_SEGMENT].base = 0x0;
    segs[CODE_SEGMENT]._base = 0x0;
    segs[CODE_SEGMENT].pptf = 0b10011010;
    segs[CODE_SEGMENT].other = 0b11001111;
    segs[CODE_SEGMENT].__base = 0x0;

    // Data Segment
    segs[DATA_SEGMENT].limit = 0xFFFF;
    segs[DATA_SEGMENT].base = 0x0;
    segs[DATA_SEGMENT]._base = 0x0;
    segs[DATA_SEGMENT].pptf = 0b10010010;
    segs[DATA_SEGMENT].other = 0b11001111;
    segs[DATA_SEGMENT].__base = 0x0;

    __asm__ __volatile__(
        "cli\n"
        "lgdt %0" ::"m"(gdt));
}