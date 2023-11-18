#include <string.h>

#include "gdt.h"
#include "vga.h"

void kernel_main(void)
{
	gdtInit(); // Multiboot already sets a GDT, but we need our own later

	vgaInit(BLACK);
	const char* prompt = " > ";
	vgaPrint("SO - Sistema Operativo!\n");
	vgaPrint(prompt);
	while(1);
}