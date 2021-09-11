#ifndef INCLUDE_ISR_H
#define INCLUDE_ISR_H

#pragma once
#include "utils/types.h"
#include <stdint.h>

typedef struct cpu_state {
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t esp;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;
} cpu_state_t;

typedef struct stack_state {
  uint32_t int_no;
  uint32_t err_code;
  uint32_t eip;
  uint32_t cs;
  uint32_t eflags;
  uint32_t useresp;
  uint32_t ss;
} stack_state_t;

typedef struct registers {
  /* Data segment selector */
  uint32_t ds;
  /* Pushed by pusha */
  cpu_state_t cpu_registers;
  /* Interrupt number and error code (if applicable). Pushed by the processor
   * automatically.
   */
  stack_state_t stack_contents;
} registers_t;

typedef void (*isr_t)(registers_t);

void register_interrupt_handler(uint8_t n, isr_t handler);

/* Function to initialize IDT */
void init_idt();

#endif /* INCLUDE_ISR_H */