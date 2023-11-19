#include "idt.h"

#include "io.h"
#include "nice.h"

typedef struct
{
    u16 limit;
    u32 base;
} PACKED(InterruptDescriptorTable);

typedef struct
{
    u16 isr;
    u16 kernelCS;
    u8 reserved;
    u8 attributes;
    u16 _isr;
} PACKED(IDTEntry);

IDTEntry idts[256];
InterruptDescriptorTable idt;

void idtSetDescriptor(u8 i, u32 isr, u8 flags)
{
    idts[i].isr = (u16)isr & 0xFFFF;
    idts[i].kernelCS = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    idts[i].reserved = 0;
    idts[i].attributes = flags;
    idts[i]._isr = (u16)isr >> 16;
}

void idtLoad()
{
    idt.limit = sizeof(IDTEntry) * 256 - 1;
    idt.base = (u32)&idts;

    __asm__ __volatile__(
        "lidt (%0)\n"
        "sti" ::"r"(&idt));
}