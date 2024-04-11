#include "os.h"

extern void switch_to(struct context *next);

#define MAX_TASKS 10
#define STACK_SIZE 1024

/*
 * In the standard RISC-V calling convention, the stack pointer sp
 * is always 16-byte aligned.
 */

uint8_t __attribute__((aligned(16))) task_stack[MAX_TASKS][STACK_SIZE];
struct context ctx_tasks[MAX_TASKS];

static int _top = 0;      // current number of task
static int _current = -1; // point to the context of current task

void user_task0(void);

void sched_init()
{
    w_mscratch(0);
}

void schedule()
{
    if (_top <= 0)
    {
        panic("Num of task should be greater than zero!");
        return;
    }
    _current = (_current + 1) % _top;

    struct context *next = &(ctx_tasks[_current]);
    switch_to(next);
}

int task_create(void (*start_routin)(void))
{
    if (_top < MAX_TASKS)
    {
        ctx_tasks[_top].sp = (reg_t)&task_stack[_top][STACK_SIZE];
        ctx_tasks[_top].ra = (reg_t)start_routin;
        _top++;
        return 0;
    }
    return -1;
}

void task_yield()
{
    schedule();
}

void task_delay(volatile int count)
{
    count *= 50000;
    while (count--)
        ;
}