; C runtime initialization

.section .init
.global _init
.type _init, @function
_init:
    push %ebp
    movl %esp, %ebp
    ; gcc will put the contents of crtbegin.o's .init section here

.section .fini
.global .fini
.type _fini, @function
_fini:
    push %ebp
    movl %esp, %ebp
    ; gcc will put the contents of crtfini.o's .fini section here

