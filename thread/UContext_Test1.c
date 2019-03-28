#include <stdio.h>
#include <unistd.h>
#include "UContext.h"

#define THREAD_POOL_SIZE 1000000

/* 线程池或者协程池 */
static int thread_index = 0;
static Thread_t thread_pool[THREAD_POOL_SIZE];

void* thread_func(void* arg)
{
    int size = THREAD_POOL_SIZE;
    while (1) {
        int temp = (thread_index % size);
        thread_index = ((temp + 1) % size);
        printf("Thread ID[%d] is doing stuff with stack top[%p] curr:%d:next:%d\n", thread_pool[temp].id, thread_pool[temp].stack_esp, temp, thread_index);
	    Thread_switch(&thread_pool[temp], &thread_pool[thread_index]);  //switch to thread B
        /* when switch back, exectution restarts from here */
        //sleep(1);  //pretends to be busy in this thread. But this actually blocks the whole process.
    }
    return NULL;
}

int main()
{
    int size = THREAD_POOL_SIZE;
    for (int i = 0; i < size; i++) {
        Thread_create_with_ID(&thread_pool[i], i, thread_func);
    }
 
    /* 保存主线程的上下文 */
    Thread_start_with_save(&thread_pool[0]);

    for (int i = 0; i < size; i++) {
        Thread_destroy(&thread_pool[i]);
    }

    return 0;    
}
