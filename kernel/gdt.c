#include "gdt.h"

GDTEntry gdt[NUM_SEGMENTS];
GDTPtr gdt_ptr;

void gdt_main()
{
    gdt_ptr.limit = (sizeof(GDTEntry) * NUM_SEGMENTS) - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    asm volatile("lgdt [%0]" : : "m" (gdt_ptr));
}

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access = access;
}
