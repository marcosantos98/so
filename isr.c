#include "isr.h"

#include "idt.h"
#include "io.h"
#include "vga.h"

#include "nice.h"

isr_t interrupt_handlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
    idtSetDescriptor(0, (u32) isr0, 0x8E);
    idtSetDescriptor(1, (u32) isr1, 0x8E);
    idtSetDescriptor(2, (u32) isr2, 0x8E);
    idtSetDescriptor(3, (u32) isr3, 0x8E);
    idtSetDescriptor(4, (u32) isr4, 0x8E);
    idtSetDescriptor(5, (u32) isr5, 0x8E);
    idtSetDescriptor(6, (u32) isr6, 0x8E);
    idtSetDescriptor(7, (u32) isr7, 0x8E);
    idtSetDescriptor(8, (u32) isr8, 0x8E);
    idtSetDescriptor(9, (u32) isr9, 0x8E);
    idtSetDescriptor(10, (u32) isr10, 0x8E);
    idtSetDescriptor(11, (u32) isr11, 0x8E);
    idtSetDescriptor(12, (u32) isr12, 0x8E);
    idtSetDescriptor(13, (u32) isr13, 0x8E);
    idtSetDescriptor(14, (u32) isr14, 0x8E);
    idtSetDescriptor(15, (u32) isr15, 0x8E);
    idtSetDescriptor(16, (u32) isr16, 0x8E);
    idtSetDescriptor(17, (u32) isr17, 0x8E);
    idtSetDescriptor(18, (u32) isr18, 0x8E);
    idtSetDescriptor(19, (u32) isr19, 0x8E);
    idtSetDescriptor(20, (u32) isr20, 0x8E);
    idtSetDescriptor(21, (u32) isr21, 0x8E);
    idtSetDescriptor(22, (u32) isr22, 0x8E);
    idtSetDescriptor(23, (u32) isr23, 0x8E);
    idtSetDescriptor(24, (u32) isr24, 0x8E);
    idtSetDescriptor(25, (u32) isr25, 0x8E);
    idtSetDescriptor(26, (u32) isr26, 0x8E);
    idtSetDescriptor(27, (u32) isr27, 0x8E);
    idtSetDescriptor(28, (u32) isr28, 0x8E);
    idtSetDescriptor(29, (u32) isr29, 0x8E);
    idtSetDescriptor(30, (u32) isr30, 0x8E);
    idtSetDescriptor(31, (u32) isr31, 0x8E);

    // Remap the PIC
    ioWrite(0x20, 0x11);
    ioWrite(0xA0, 0x11);
    ioWrite(0x21, 0x20);
    ioWrite(0xA1, 0x28);
    ioWrite(0x21, 0x04);
    ioWrite(0xA1, 0x02);
    ioWrite(0x21, 0x01);
    ioWrite(0xA1, 0x01);
    ioWrite(0x21, 0x0);
    ioWrite(0xA1, 0x0);

    // Install the IRQs
    idtSetDescriptor(32, (u32)irq0, 0x8E);
    idtSetDescriptor(33, (u32)irq1, 0x8E);
    idtSetDescriptor(34, (u32)irq2, 0x8E);
    idtSetDescriptor(35, (u32)irq3, 0x8E);
    idtSetDescriptor(36, (u32)irq4, 0x8E);
    idtSetDescriptor(37, (u32)irq5, 0x8E);
    idtSetDescriptor(38, (u32)irq6, 0x8E);
    idtSetDescriptor(39, (u32)irq7, 0x8E);
    idtSetDescriptor(40, (u32)irq8, 0x8E);
    idtSetDescriptor(41, (u32)irq9, 0x8E);
    idtSetDescriptor(42, (u32)irq10, 0x8E);
    idtSetDescriptor(43, (u32)irq11, 0x8E);
    idtSetDescriptor(44, (u32)irq12, 0x8E);
    idtSetDescriptor(45, (u32)irq13, 0x8E);
    idtSetDescriptor(46, (u32)irq14, 0x8E);
    idtSetDescriptor(47, (u32)irq15, 0x8E);

    idtLoad();
}

/* To print the message which defines every exception */
char *exception_messages[] = {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",

        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",

        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",

        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
};

void isr_handler(registers_t *r) {
    vgaPrint("received interrupt: ");
    // char s[3];
    // int_to_string(r->int_no, s);
    // print_string(s);
    // print_nl();
    // print_string(exception_messages[r->int_no]);
    // print_nl();
}

void register_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t *r) {
    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }

    // EOI
    if (r->int_no >= 40) {
        ioWrite(0xA0, 0x20); /* follower */
    }
    ioWrite(0x20, 0x20); /* leader */
}