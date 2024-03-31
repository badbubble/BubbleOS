# BubbleOS: A Simple RISC-V Operating System in C

BubbleOS is a demonstration operating system for personal educational purposes, aimed at providing insight into the fundamentals of operating system development.

This OS is based on materials from [here](https://github.com/plctlab/riscv-operating-system-mooc).
## Overview
This project serves as a practical learning resource for those interested in understanding the essentials of OS development. It offers a hands-on approach to exploring concepts like task scheduling, memory management, and basic I/O operation.

## Future Development
In the future, BubbleOS will undergo a major overhaul and transition to Rust programming language. This transition will introduce advanced features including Virtual Memory support, File Systems implementation, and Network components integration.
## Boot

## UART

## Memory Management
![Memory Management](.github/memory_management.png)

The length of Memory is 128M = 8 managment pages * 4096 bytes * 4096 page size

BubbleOS utilizes a page-based memory management system. The first 8 pages are dedicated to management, followed by real pages for data storage. Each byte within the management pages stores a flag, where the last two bits represent PAGE_LAST (indicating if the page is the last page of an allocation) and PAGE_TAKEN (indicating if the page is currently in use).

For example, a flag value of 0x0000_0001 signifies that the page is currently in use and is not the last page of an allocation.

## Cooperative Multitasking


In Cooperative Multitasking, before a new task can be executed, the current one must voluntarily give up the CPU.

* `mscratch`: A register in Machine mode to point current context
* `ra(x1)`: General register to save the return address
* `ret`: jump back to `ra`
* `call`: will also store the next address of instruction into `ra`
![cooperative](.github/cooperative.png)
There are two tasks, A and B. Task A is running on the CPU. When it calls `switch_to` to switch to task B, it stores the address of the next instruction of task A in the `ra` register before entering the `switch_to` function in BubbleOS. Inside `switch_to`, it saves the context of task A into memory, then restores the context of task B from memory on top of that in order to execute the instructions for task B it `ret`(jump to the instruction in B).
