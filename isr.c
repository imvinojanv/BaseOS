#include "isr.h"
#include "utils/common/common.h"
#include "io.h"
#include "utils/log.h"

isr_t interrupt_handlers[256];
const uint8_t TIME_INTERRUPT_NUMBER = 32;
const uint8_t KEYBOARD_INTERRUPT_NUMBER = 33;

/* Function to register interrupt handler with custom call back function */
void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}