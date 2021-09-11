#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#pragma once
#include "types.h"

/** print_serial:
 *  writes the char array buffer of length len to serial console
 *
 *  @param buffer  Buffer that has contents to be written to serial port
 */
void print_serial(s8int buffer[]);

/** print_serial:
 *  writes the char to serial console
 *
 *  @param ch  Buffer that has contents to be written to serial port
 */
void print_serial_ch(s8int ch);

/** print_screen:
 *  writes the char buffer buf of length len to Screen
 *
 *  @param buffer  Buffer that has contents to be written to Screen
 */
void print_screen(s8int buffer[]);

/** print_screen:
 *  writes the char to Screen
 *
 *  @param ch  Buffer that has contents to be written to Screen
 */
void print_screen_ch(s8int ch);

/** init_display:
 *  Initializes the frame buffer
 */
void init_display();

#endif /* INCLUDE_LOGGER_H */
