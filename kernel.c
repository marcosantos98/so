#include <string.h>

#include "vga.h"

void kernel_main(void)
{
	vgaInit(BLACK);
	vgaPrint("Hello World!");
	while(1);
}