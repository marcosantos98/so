LD = toolchain/cross/bin/i686-elf-ld
GCC = toolchain/cross/bin/i686-elf-gcc

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./c/

asm_src = bin/boot.o
kernel_src = bin/kernel.o bin/vga.o bin/gdt.o

misc_output = bin/so.bin

bin/%.o: %.c
	$(GCC) -c $< -o $@ $(CFLAGS)

bin/%.o: %.asm
	nasm -f elf32 $< -o $@

bin/so.bin: link.ld $(asm_src) $(kernel_src)
	$(LD) -T $< -o $@ $(asm_src) $(kernel_src)

clean:
	rm -f $(asm_src)
	rm -f $(kernel_src)
	rm -f $(misc_output)

run:
	qemu-system-i386 -kernel bin/so.bin