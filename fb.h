    #ifndef INCLUDE_FB_H
    #define INCLUDE_FB_H

    #include "io.h"

    /* The I/O ports */
    #define FB_COMMAND_PORT         0x3D4
    #define FB_DATA_PORT            0x3D5

    /* The I/O port commands */
    #define FB_HIGH_BYTE_COMMAND    14
    #define FB_LOW_BYTE_COMMAND     15

    #define FB_GREEN     2
    #define FB_DARK_GREY 8

    char *fb = (char *) 0x00B8000;

    /** fb_write_cell:
     *  Writes a character with the given foreground and background to position i
     *  in the framebuffer.
     *
     *  @param i  The location in the framebuffer
     *  @param c  The character
     *  @param fg The foreground color
     *  @param bg The background color
     */
    void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
    {
        fb[i*2] = c;
        fb[i*2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
    }

    /** fb_move_cursor:
     *  Moves the cursor of the framebuffer to the given position
     *
     *  @param pos The new position of the cursor
     */
    void fb_move_cursor(unsigned short pos)
    {
        outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT,    pos & 0x00FF);
    }

    int write(char *buf, unsigned int len)
    {
        unsigned int i = 0;
        for ( i = 0; i < len; i++)
        {
            fb_write_cell(i, buf[i], FB_GREEN, FB_DARK_GREY);
        }
        return 0;
       
    }

    #endif
