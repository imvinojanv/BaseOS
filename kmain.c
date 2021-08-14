#include "io.h"
#include "fb.h"
#include "serial_port.h"
#include "memory_segments.h"

    /* The C function */
    int sum_of_three(int arg1, int arg2, int arg3)
    {
        return arg1 + arg2 + arg3;
    }
    
    void run(){
        char c[] = "Welcome";
        write(c, 9);

        serial_write(SERIAL_COM1_BASE, c, 7);
        segments_install_gdt();
        
    }
    
