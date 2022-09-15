bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002              ;magic
        dd 0x00                    ;flags
        dd - (0x1BADB002 + 0x00)   ;checksum. m+f+c should be zero

global _start
global keyboard_handler
global load_idt
global gdt_flush

extern kernel_main 		;this is defined in the c file
extern keyboard_handler_main

gdt_flush:
	mov edx, [esp + 4]
	lgdt [edx]
	mov ax, 0x10      
	mov ds, ax        
    mov fs, ax
    mov gs, ax
    mov ss, ax				
	jmp 0x08:.flush ; Far jump

.flush:
	ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti 				;turn on interrupts
	ret

keyboard_handler:                 
	call    keyboard_handler_main
	iretd

_start:
	cli 				;block interrupts
	mov esp, stack_space
	call kernel_main
	hlt 				;halt the CPU

section .bss
resb 8192; 8KB for stack
stack_space:
