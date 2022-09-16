LD = toolchain/cross/bin/i686-elf-ld
GCC = toolchain/cross/bin/i686-elf-gcc

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

asm_src = boot.o kernel/interrupts.o
kernel_src = kernel/kernel.o kernel/gdt.o kernel/idt.o kernel/io.o kernel/isr.o
kernel_device_src = kernel/device/video.o kernel/device/keyboard.o
libc_src = libc/string.o
misc_output = so.bin

%.o: %.c
	$(GCC) -c $< -o $@ $(CFLAGS)

%.o: %.s
	nasm -f elf32 $< -o $@

so.bin: link.ld $(asm_src) $(kernel_src) $(kernel_device_src) $(libc_src)
	$(LD) -T $< -o $@ $(asm_src) $(kernel_src) $(kernel_device_src) $(libc_src)

clean:
	rm $(asm_src)
	rm $(kernel_src)
	rm $(kernel_device_src)
	rm $(libc_src)
	rm $(misc_output)

run:
	qemu-system-i386 -kernel so.bin -d int -D log.txt