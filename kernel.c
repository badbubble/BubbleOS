#include "os.h"

extern void uart_init(void);
extern void page_init(void);
extern void page_test(void);
void start_kernel(void)
{
    uart_init();
    page_init();
    uart_puts("-----------------------------\n");
    uart_puts("Hello, BubbleOS!\n");

    while (1)
    {
    }
}