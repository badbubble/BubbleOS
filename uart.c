#include "platform.h"
#include "types.h"

// This marco returns the address of required registers
#define UART_REG(reg) ((volatile uint8_t *)(UART0 + reg))

// read/write from/to registers
#define uart_read_reg(reg) (*(UART_REG(reg)))
#define uart_write_reg(reg, v) (*(UART_REG(reg)) = (v))

#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE  (1 << 5)

// UART control registers
#define RHR 0	// Receive Holding Register (read mode)
#define THR 0	// Transmit Holding Register (write mode)
#define DLL 0	// LSB of Divisor Latch (write mode)
#define IER 1	// Interrupt Enable Register (write mode)
#define DLM 1	// MSB of Divisor Latch (write mode)
#define FCR 2	// FIFO Control Register (write mode)
#define ISR 2	// Interrupt Status Register (read mode)
#define LCR 3	// Line Control Register
#define MCR 4	// Modem Control Register
#define LSR 5	// Line Status Register
#define MSR 6	// Modem Status Register
#define SPR 7	// ScratchPad Register


void uart_init()
{
/*
 * POWER UP DEFAULTS
 * IER = 0: TX/RX holding register interrupts are both disabled
 * ISR = 1: no interrupt penting
 * LCR = 0
 * MCR = 0
 * LSR = 60 HEX
 * MSR = BITS 0-3 = 0, BITS 4-7 = inputs
 * FCR = 0
 * TX = High
 * OP1 = High
 * OP2 = High
 * RTS = High
 * DTR = High
 * RXRDY = High
 * TXRDY = Low
 * INT = Low
 */
    // Disable interrupts
    uart_write_reg(IER, 0x00); // last two bits are THR and RHR interrupt
    // Setting baud rate
    uint8_t lcr = uart_read_reg(LCR);
    uart_write_reg(LCR, lcr | (1 << 7)); // divisor latch enable

    uart_write_reg(DLL, 0x03);
	uart_write_reg(DLM, 0x00);
    // Setting communication format
    lcr = 0;
    uart_write_reg(LCR, lcr | (3 << 0));
}

int uart_putc(char ch)
{
    while((uart_read_reg(LSR) & LSR_TX_IDLE) == 0);
    return uart_write_reg(THR, ch);
}

void uart_puts(char *s)
{
    while (*s)
    {
        uart_putc(*s++);
    }
}