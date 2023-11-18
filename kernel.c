#include <string.h>

#include "vga.h"

void kernel_main(void)
{
	vgaInit(BLACK);
	const char* prompt = " > ";
	vgaPrint("SO - Sistema Operativo!\n");
	vgaPrint(prompt);
	while(1);
}