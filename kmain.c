#include "serial_port.h"
#include "memory_segments.h"
#include "interrupts.h"
#include "multiboot.h"
#include "paging.h"

void init(){
   segments_install_gdt();
   interrupts_install_idt();
   init_paging();
}

int kmain(unsigned int ebx){
   
   init();

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
