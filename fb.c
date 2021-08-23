#include "fb.h"

static char *fb = (char *)FB_BASE_ADDRESS;

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
  fb[2 * i] = c;
  fb[2 * i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

int fb_write(char *buf, unsigned int len) {
  unsigned int indexToBuffer = 0;
  while (indexToBuffer < len) {
    fb_write_cell(indexToBuffer, buf[indexToBuffer], FB_GREEN, FB_DARK_GREY);
    fb_move_cursor(indexToBuffer);
    indexToBuffer++;
  }
  return 0;
}
