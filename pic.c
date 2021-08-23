#include "io.h"
#include "pic.h"


void pic_acknowledge(unsigned int interrupt)
{
	if (interrupt < PIC_1_OFFSET || interrupt > PIC_2_END) {
		return;
	}

	if (interrupt < PIC_2_OFFSET) {
		outb(PIC_1_COMMAND_PORT, PIC_ACKNOWLEDGE);
	} else {
		outb(PIC_2_COMMAND_PORT, PIC_ACKNOWLEDGE);
	}
}


void pic_remap(int offset1, int offset2)
{
	outb(PIC_1_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);	
	outb(PIC_2_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
	outb(PIC_1_DATA, offset1);				
	outb(PIC_2_DATA, offset2);				
	outb(PIC_1_DATA, 4);					
	outb(PIC_2_DATA, 2);					 

	outb(PIC_1_DATA, PIC_ICW4_8086);
	outb(PIC_2_DATA, PIC_ICW4_8086);

        
	outb(PIC_1_DATA, 0xFD); 
	outb(PIC_2_DATA, 0xFF);

	asm("sti"); 
}
