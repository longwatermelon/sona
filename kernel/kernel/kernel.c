#include <kernel/tty.h>
#include <kernel/vga.h>
#include <stdio.h>

void kmain()
{
    term_init();
    printf("test 1\ntest 2\n");
    printf("test\nnewline");
}

