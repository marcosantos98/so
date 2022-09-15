#ifndef IDT_ENTRY
#define IDT_ENTRY

#include <stdint.h>

#define IDT_SIZE 256

struct IDTEntry
{
    uint16_t base_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

struct IDTPtr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

typedef struct IDTEntry IDTEntry;
typedef struct IDTPtr IDTPtr;

extern void load_idt(uint32_t);

void idt_main();
void idt_set_gate(uint8_t num, unsigned long base, unsigned short sel, uint8_t flags);

#endif