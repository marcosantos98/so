#include "idt.h"

#include "device/keyboard.h"
#include "io.h"
#include "isr.h"
#include "device/video.h"

IDTEntry idt[IDT_SIZE] = {0};
IDTPtr idt_ptr;

/*https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard*/
void idt_main()
{

	idt_ptr.limit = (sizeof(IDTEntry) * IDT_SIZE) - 1;
	idt_ptr.base = (uint32_t)&idt;

	idt_set_gate(0, (unsigned long)isr0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned long)isr1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned long)isr2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned long)isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned long)isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned long)isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned long)isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned long)isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned long)isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned long)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned long)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned long)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned long)isr31, 0x08, 0x8E);

	// Keyboard
	//idt_set_gate(0x21, (unsigned long)keyboard_handler, 0x08, 0x8E);

	// /*     Ports
	//  *	 PIC1	PIC2
	//  *Command 0x20	0xA0
	//  *Data	 0x21	0xA1
	//  */

	// /* ICW1 - begin initialization */
	// io_write(0x20, 0x11);
	// io_write(0xA0, 0x11);

	// /* ICW2 - remap offset address of IDT */
	// /*
	//  * In x86 protected mode, we have to remap the PICs beyond 0x20 because
	//  * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	//  */
	// io_write(0x21, 0x20);
	// io_write(0xA1, 0x28);

	// /* ICW3 - setup cascading */
	// io_write(0x21, 0x00);
	// io_write(0xA1, 0x00);

	// /* ICW4 - environment info */
	// io_write(0x21, 0x01);
	// io_write(0xA1, 0x01);
	// /* Initialization finished */

	// /* mask interrupts */
	// io_write(0x21, 0xff);
	// io_write(0xA1, 0xff);

	load_idt((uint32_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, unsigned long base, unsigned short sel, uint8_t flags)
{
	idt[num].base_low = (base & 0xFFFF);
	idt[num].sel = sel;
	idt[num].zero = 0;
	idt[num].flags = flags;
	//idt[num].base_hi = (base & 0xFFFF0000) >> 16;
	idt[num].base_hi = (base >> 16) && 0xFFFF;
}