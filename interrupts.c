#include "interrupts.h"
#include "pic.h"
#include "io.h"
#include "serial_port.h"
#include "keyboard.h"

#define INTERRUPTS_DESCRIPTOR_COUNT 256 
#define INTERRUPTS_KEYBOARD 33 
#define INTERRUPTS_PAGING 14 

struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;


void interrupts_init_descriptor(int index, unsigned int address)
{
	idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF; // offset bits 0..15
	idt_descriptors[index].offset_low = (address & 0xFFFF); // offset bits 16..31

	idt_descriptors[index].segment_selector = 0x08; // The second (code) segment selector in GDT: one segment is 64b.
	idt_descriptors[index].reserved = 0x00; // Reserved.

	idt_descriptors[index].type_and_attr =	(0x01 << 7) |			// P
						(0x00 << 6) | (0x00 << 5) |	// DPL
						0xe;				// 0b1110=0xE 32-bit interrupt gate
}


void interrupts_install_idt()
{
	interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (unsigned int) interrupt_handler_33);
	interrupts_init_descriptor(INTERRUPTS_PAGING, (unsigned int) interrupt_handler_14);

	idt.address = (int) &idt_descriptors;
	idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
	load_idt((int) &idt);

	pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
}


void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, unsigned int interrupt, __attribute__((unused)) struct stack_state stack)
{
	unsigned char scan_code;
	unsigned char ascii;

	switch (interrupt){
		case INTERRUPTS_KEYBOARD:

			scan_code = keyboard_read_scan_code();

			if (scan_code <= KEYBOARD_MAX_ASCII) {
				ascii = keyboard_scan_code_to_ascii(scan_code);
				serial_configure_baud_rate(SERIAL_COM1_BASE, 4);
				serial_configure_line(SERIAL_COM1_BASE);
				char str[1];
				str[0] = ascii;
				serial_write(str, 1);
			}

			pic_acknowledge(interrupt);

			break;
		default:
			break;
    }
}
