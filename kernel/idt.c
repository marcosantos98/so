#include "idt.h"

#include "keyboard.h"
#include "io.h"
#include "video.h"

IDTEntry idt[IDT_SIZE] = {0};
IDTPtr idt_ptr;

/*https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard*/
void idt_main()
{

    idt_ptr.limit = (sizeof(IDTEntry) * IDT_SIZE) - 1;
    idt_ptr.base = (uint32_t)&idt;

    idt_set_gate(0x21, (unsigned long)keyboard_handler, 0x08, 0x8E);

    /*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	io_write(0x20 , 0x11);
	io_write(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	io_write(0x21 , 0x20);
	io_write(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	io_write(0x21 , 0x00);
	io_write(0xA1 , 0x00);

	/* ICW4 - environment info */
	io_write(0x21 , 0x01);
	io_write(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	io_write(0x21 , 0xff);
	io_write(0xA1 , 0xff);

    load_idt((uint32_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, unsigned long base, unsigned short sel, uint8_t flags)
{
    idt[num].base_low = (base & 0xFFFF);
    idt[num].sel = sel;
    idt[num].zero = 0;
    idt[num].flags = flags;
    idt[num].base_hi = (base & 0xFFFF0000) >> 16;
}