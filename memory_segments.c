#include "memory_segments.h"

#define SEGMENT_DESCRIPTOR_COUNT 3
#define SEGMENT_BASE 0
#define SEGMENT_LIMIT 0xFFFFF
#define SEGMENT_CODE_TYPE 0x9A
#define SEGMENT_DATA_TYPE 0x92
#define SEGMENT_FLAGS_PART 0x0C


static struct GDTDescriptor gdt_descriptors[SEGMENT_DESCRIPTOR_COUNT];


void segments_init_descriptor(int index, unsigned int base_address, unsigned int limit, unsigned char access_byte, unsigned char flags){
	gdt_descriptors[index].base_low = base_address & 0xFFFF;
	gdt_descriptors[index].base_middle = (base_address >> 16) & 0xFF;
	gdt_descriptors[index].base_high = (base_address >> 24) & 0xFF;

	gdt_descriptors[index].limit_low = limit & 0xFFFF;
	gdt_descriptors[index].limit_and_flags = (limit >> 16) & 0xF;
	gdt_descriptors[index].limit_and_flags |= (flags << 4) & 0xF0;

	gdt_descriptors[index].access_byte = access_byte;
}


void segments_install_gdt(){
	gdt_descriptors[0].base_low = 0;
	gdt_descriptors[0].base_middle = 0;
	gdt_descriptors[0].base_high = 0;
	gdt_descriptors[0].limit_low = 0;
	gdt_descriptors[0].access_byte = 0;
	gdt_descriptors[0].limit_and_flags = 0;

	struct GDT* gdt_ptr = (struct GDT*)gdt_descriptors;
	gdt_ptr->address = (unsigned int)gdt_descriptors;
	gdt_ptr->size = (sizeof(struct GDTDescriptor) * SEGMENT_DESCRIPTOR_COUNT) - 1;

	segments_init_descriptor(1, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_CODE_TYPE, SEGMENT_FLAGS_PART);
	segments_init_descriptor(2, SEGMENT_BASE, SEGMENT_LIMIT, SEGMENT_DATA_TYPE, SEGMENT_FLAGS_PART);

	segments_load_gdt(*gdt_ptr);
	segments_load_registers();
}
