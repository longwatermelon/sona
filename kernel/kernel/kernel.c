#include <kernel/tty.h>
#include <kernel/vga.h>
#include <stdio.h>

void kernel_main()
{
    term_init();
    printf("test 1\ntest 2\n");
    printf("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\nend\nhoo\na\nb\nc\nd");
}

