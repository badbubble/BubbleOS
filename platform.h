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

#define UART0_IRQ 10
#define PLIC_BASE 0x0c000000L

#define PLIC_BASE 0x0c000000L
#define PLIC_PRIORITY(id) (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id) (PLIC_BASE + 0x1000 + ((id) / 32) * 4)
#define PLIC_MENABLE(hart, id) (PLIC_BASE + 0x2000 + (hart) * 0x80 + ((id) / 32) * 4)
#define PLIC_MTHRESHOLD(hart) (PLIC_BASE + 0x200000 + (hart) * 0x1000)
#define PLIC_MCLAIM(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)
#define PLIC_MCOMPLETE(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)


#endif /* __PLATFORM_H__ */
