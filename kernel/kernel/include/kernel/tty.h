#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void term_init();
void term_write(const char* data);
void term_color(uint8_t color);

#endif

