#include "fb.h"
#include "serial_port.h"
#include "memory_segments.h"
#include "keyboard.h"
#include "interrupts.h"


    
void kmain(){

    //char msg[] = "welcome";
    unsigned char scancode,ascii;
    char asciicode[1];
   
    segments_install_gdt();
    //serial_write(msg, sizeof(msg));
    //fb_write(msg, sizeof(msg));
    interrupts_install_idt();
    scancode = keyboard_read_scan_code();
    ascii = keyboard_scan_code_to_ascii(scancode);
    asciicode[0] = ascii;
    serial_write(asciicode, sizeof(asciicode));
    //fb_write(asciicode, sizeof(asciicode));
    
}
