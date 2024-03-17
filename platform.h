#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/*
 * QEMU RISC-V Virt machine with 16550a UART and VirtIO MMIO
 */

/* 
 * maximum number of CPUs
 * #define VIRT_CPUS_MAX 8
 */
#define MAXNUM_CPU 8

/* Memory map*/
// UART Registers
#define UART0 0x10000000L

#endif /* __PLATFORM_H__ */
