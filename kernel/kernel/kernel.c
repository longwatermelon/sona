#include <kernel/tty.h>
#include <kernel/vga.h>
#include <stdio.h>

void kernel_main() {
    term_init();
    printf("hoo hoo\ntest\n");
    term_color(vga_color(VGA_COLOR_CYAN, VGA_COLOR_BLUE));
    printf("color\n");
}

