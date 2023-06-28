#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void term_init();
void term_write(const char* data);

#endif

