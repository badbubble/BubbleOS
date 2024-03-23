# BubbleOS: A Simple RISC-V Operating System in C

BubbleOS is a demonstration operating system for personal educational purposes, aimed at providing insight into the fundamentals of operating system development.

This OS is based on materials from [here](https://github.com/plctlab/riscv-operating-system-mooc).
## Overview
This project serves as a practical learning resource for those interested in understanding the essentials of OS development. It offers a hands-on approach to exploring concepts like task scheduling, memory management, and basic I/O operation.

## Future Development
In the future, BubbleOS will undergo a major overhaul and transition to Rust programming language. This transition will introduce advanced features including Virtual Memory support, File Systems implementation, and Network components integration.

## Memory Management
![Memory Management](.github/memory_management.png)
BubbleOS utilizes a page-based memory management system. The first 8 pages are dedicated to management, followed by real pages for data storage. Each byte within the management pages stores a flag, where the last two bits represent PAGE_LAST (indicating if the page is the last page of an allocation) and PAGE_TAKEN (indicating if the page is currently in use).

For example, a flag value of 0x0000_0001 signifies that the page is currently in use and is not the last page of an allocation.
