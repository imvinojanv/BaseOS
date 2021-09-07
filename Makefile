    OBJECTS = loader.o kmain.o io.o fb.o serial_port.o memory_segments.o gdt.o interrupts.o interrupt_handlers.o pic.o keyboard.o idt.o common.o paging.o paging_enable.o memory.o isr.o
    CC = gcc
    CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector \
         -Wno-unused -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -masm=intel
    LDFLAGS = -T link.ld -melf_i386
    AS = nasm
    ASFLAGS = -f elf

    all: kernel.elf

    kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

    os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
                    -b boot/grub/stage2_eltorito    \
                    -no-emul-boot                   \
                    -boot-load-size 4               \
                    -A os                           \
                    -input-charset utf8             \
                    -quiet                          \
                    -boot-info-table                \
                    -o os.iso                       \
                    iso

    run: os.iso
	bochs -f bochsrc.txt -q

    %.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

    %.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

    clean:
	rm -rf *.o kernel.elf os.iso

