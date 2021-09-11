#include "serial_port.h"
#include "memory_segments.h"
#include "interrupts.h"
#include "multiboot.h"
#include "paging/paging.h"

void init(u32int kernelPhysicalStart, u32int kernelPhysicalEnd){
   segments_install_gdt();
   interrupts_install_idt();
   init_paging(kernelPhysicalStart, kernelPhysicalEnd);
}

int kmain(unsigned int ebx, u32int kernel_physical_start, u32int kernel_physical_end){
   
   init(kernel_physical_start, kernel_physical_end);

   multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
   multiboot_module_t* modules = (multiboot_module_t*) mbinfo->mods_addr; 
   unsigned int address_of_module = modules->mod_start;

   if((mbinfo->mods_count) == 1){
      char str[] = "Module successfully loaded\n";
      serial_write(str,sizeof(str));
      
      typedef void (*call_module_t)(void);
         call_module_t start_program = (call_module_t) address_of_module;
         start_program();

   }
   else{
      char str[] = "Multiple modules loaded\n";
      serial_write(str,sizeof(str));
   }

   return 0;
}
