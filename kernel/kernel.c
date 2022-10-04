#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"
#include "idt.h"
#include "device/video.h"
#include "device/keyboard.h"

void kernel_main(void)
{
	video_main();
	video_clear_mem();
	video_write_cstr("Initializing GDT\n");
	gdt_main();
	video_write_cstr("Initializing IDT\n");
	idt_main();	
	video_write_cstr("Enable Keyboard\n");
	keyboard_enable();	

	video_write_cstr("With numbers now! ");
	video_put_dec(6969420);
	video_put_char('\n');

	while(1);
}