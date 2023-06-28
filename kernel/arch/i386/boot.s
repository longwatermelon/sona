# Declare constants for multiboot header
.set ALIGN, 1<<0 # Loaded modules should be aligned on page boundaries
.set MEMINFO, 1<<1 # Should provide memory map
.set FLAGS, ALIGN | MEMINFO # Multiboot uses this flags variable
.set MAGIC, 0x1BADB002 # Magic number allows bootloader to find header
.set CHECKSUM, -(MAGIC + FLAGS) # Prove that we are inside multiboot

# Declare header as in multiboot standard
.section .multiboot
.align 4 # Ensure that the header starts at an address that is a multiple of 4 bytes
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread
.section .bss

# Stack must be 16-byte aligned according to the System V ABI standard
# If it isn't, it will cause undefined behavior
.align 16

# Stack grows downwards, so stack_bottom comes first
# Reserve 16 kb for the stack
stack_bottom:
.skip 16384 # 16 kb
stack_top:

# Kernel entry point
.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp

    # Call global constructors
    call _init

    # Transfer control to main kernel
    call kmain

    # Hang if kernel_main unexpectedly returns
    cli # Disable maskable interrupts
1:  hlt # Halt
    jmp 1b # If hlt is interrupted (non-maskable), jump back to hlt

.size _start, . - _start

