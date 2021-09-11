ENTRY(loader)                /* the name of the entry label */

SECTIONS {
    . = 0xC0100000  ;        /* the code should be relocated to 3 GB + 1 MB */

    /* these labels get exported to the code files */
    kernel_virtual_start = .;
    kernel_physical_start = . - 0xC0000000;

    .text ALIGN (0x1000) :   /* align at 4 KB */
    {
        *(.text)             /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) : /* align at 4 KB */
    {
        *(.rodata*)          /* all read-only data sections from all files */
    }

    .data ALIGN (0x1000) :   /* align at 4 KB */
    {
        *(.data)             /* all data sections from all files */
    }

    .bss ALIGN (0x1000) :    /* align at 4 KB */
    {
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all bss sections from all files */
    }
}

kernel_virtual_end = .;
kernel_physical_end = . - 0xC0000000;