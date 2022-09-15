# FIXME: Remove absolute paths
LD = /home/marco/opt/cross/bin/i686-elf-ld
GCC = /home/marco/opt/cross/bin/i686-elf-gcc

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

asm_src = boot.o
kernel_src = kernel/kernel.o kernel/video.o kernel/gdt.o kernel/idt.o kernel/io.o kernel/keyboard.o
libc_src = libc/string.o
misc_output = so.bin

%.o: %.c
	$(GCC) -c $< -o $@ $(CFLAGS)

%.o: %.s
	nasm -f elf32 $< -o $@

so.bin: link.ld $(asm_src) $(kernel_src) $(libc_src)
	$(LD) -T $< -o $@ $(asm_src) $(kernel_src) $(libc_src)

clean:
	rm $(asm_src)
	rm $(kernel_src)
	rm $(libc_src)
	rm $(misc_output)

run:
	qemu-system-i386 -kernel so.bin