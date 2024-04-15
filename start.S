#include "platform.h"

    # the size of each hart's stack is 1024 bytes
    # .equ is an assembler directive used to define a constant.
    .equ    STACK_SIZE, 1024
    
    # the entry point of a program to the linker.
    .global _start

    # the following section of the assembly file is the text section, which is where the executable code is placed. 
    .text

_start:
    # stop harts with id != 0
    # csrr stands for "Control and Status Register Read." 
    # It's an instruction used to read the value of a control and status register (CSR) into a general-purpose register.
    csrr    t0, mhartid # hardware thread id
    mv  tp, t0 # put in "thread pointer" register for later use
    bnez    t0, park # if it is not hart 0 jump to park

    slli    t0, t0, 10
    la  sp, stacks + STACK_SIZE

    add sp, sp, t0

    li	t0, 3 << 11 | 1 << 7
	csrs	mstatus, t0

    j start_kernel
    
park:
    # wait for interrupt instruction
    wfi
    j park
    
# .balign 16 ensures that the next piece of data or code is aligned to a 16-byte boundary in memory, which can help in optimizing program performance and preventing alignment-related faults.
.balign 16
stacks:
    .skip   STACK_SIZE * MAXNUM_CPU
    .end