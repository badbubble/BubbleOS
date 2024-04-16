#include "os.h"
#include "user_api.h"

#define DELAY 10000
#define USE_LOCK

struct userdata {
	int counter;
	char *str;
};

struct userdata person = {0, "BadBubble"};

void timer_func(void *arg)
{
    if (arg == NULL)
    {
        return;
    }
    
    struct userdata *param = (struct userdata *)arg;

	param->counter++;
	printf("======> TIMEOUT: %s: %d\n", param->str, param->counter);
}

void user_task0(void)
{
    uart_puts("[Task 0] Created!\n");
    // task_yield();
    // uart_puts("[Task 0] I am back\n");

    // struct timer *t1 = timer_create(timer_func, &person, 3);
	// if (NULL == t1) {
	// 	printf("timer_create() failed!\n");
	// }
	// struct timer *t2 = timer_create(timer_func, &person, 5);
	// if (NULL == t2) {
	// 	printf("timer_create() failed!\n");
	// }
	// struct timer *t3 = timer_create(timer_func, &person, 8);
	// if (NULL == t3) {
	// 	printf("timer_create() failed!\n");
	// }

    while (1)
    {
        uart_puts("[Task 0] Running...\n");
        // #ifdef USE_LOCK
        // spin_lock();
        // uart_puts("[Task 0] Required Lock\n");
        // #endif
        // for(int i = 0; i < 5; i++)
        // {
        //     uart_puts("[Task 0] Critical section...\n");
        //     task_delay(DELAY);
        // }
        // #ifdef USE_LOCK
        // uart_puts("[Task 0] Release Lock\n");
		// spin_unlock();

        // #endif
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

void user_task3(void)
{
    
    uart_puts("[Task 3]: Created!\n");
	unsigned int hid = -1;


#ifdef CONFIG_SYSCALL
	int ret = -1;
	ret = gethid(&hid);
	//ret = gethid(NULL);
	if (!ret) {
		printf("system call returned!, hart id is %d\n", hid);
	} else {
		printf("gethid() failed, return: %d\n", ret);
	}
#endif

	while (1){
		uart_puts("[Task 3]: Running... \n");
		task_delay(DELAY);
	}
}

void os_main(void)
{
    task_create(user_task0);
    task_create(user_task1);
    task_create(user_task3);
}
