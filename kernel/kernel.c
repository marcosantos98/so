#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"
#include "idt.h"
#include "video.h"
#include "keyboard.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
// "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
// "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

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

	while(1);
}