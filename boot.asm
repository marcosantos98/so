bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002              ;magic
        dd 0x00                    ;flags
        dd - (0x1BADB002 + 0x00)   ;checksum. m+f+c should be zero

global _start

extern kernel_main 		;this is defined in the c file

_start:
	cli 				;block interrupts
	mov esp, stack_space
	call kernel_main
	hlt 				;halt the CPU

section .bss
resb 8192; 8KB for stack
stack_space:
