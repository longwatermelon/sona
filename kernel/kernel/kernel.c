#include <kernel/tty.h>
#include <stdio.h>

void kernel_main() {
    term_init();
    printf("hoo haw");
}

