#include "os.h"

#define DELAY 10000

void user_task0(void)
{
    uart_puts("Task 0 created!\n");
    while (1)
    {
        uart_puts("Task 0 running...\n");
        trap_test();
        task_delay(DELAY);
        task_yield();
    }
}

void user_task1(void)
{
    printf("Task 1 created!\n");
    while (1)
    {
        uart_puts("Task 1 running...\n");
        task_delay(DELAY);
        task_yield();
    }
}

void os_main(void)
{
    task_create(user_task0);
    task_create(user_task1);
}
