#include "os.h"

#define DELAY 100000

#define USE_LOCK


void user_task0(void)
{
    uart_puts("[Task 0] Created!\n");
    //task_yield();
    uart_puts("[Task 0] I am back\n");
    while (1)
    {
        uart_puts("[Task 0] Running...\n");
        #ifdef USE_LOCK
        spin_lock();
        uart_puts("[Task 0] Required Lock\n");
        #endif
        for(int i = 0; i < 5; i++)
        {
            uart_puts("[Task 0] Critial section...\n");
            task_delay(DELAY);
        }
        #ifdef USE_LOCK
        uart_puts("[Task 0] Release Lock\n");
		spin_unlock();

        #endif
        task_delay(DELAY);        
    }
}

void user_task1(void)
{
    uart_puts("[Task 1] Created!\n");

    while (1)
    {
        uart_puts("[Task 1] Running...\n");
        task_delay(DELAY);
    }
}

void os_main(void)
{
    task_create(user_task0);
    task_create(user_task1);
}
