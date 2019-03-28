#include <stdio.h>
#include <unistd.h>
#include "UContext.h"

Thread_t g_thread_A;
Thread_t g_thread_B;
Thread_t g_thread_C;
 
void* func_A()
{

    while (1) {
        printf("Thread ID[%d] is executing with stack top[%p]\n", g_thread_A.id, g_thread_A.stack_esp);
        Thread_switch(&g_thread_A, &g_thread_B);  //switch to thread B
        // when switch back, exectution restarts from here
        sleep(1);  //pretends to be busy in this thread. But this actually blocks the whole process.
    }
    return NULL;
}
 
void* func_B()
{
    while (1) {
        printf("Thread ID[%d] is executing with stack top[%p]\n", g_thread_B.id, g_thread_B.stack_esp);
        Thread_switch(&g_thread_B, &g_thread_C);  //switch to thread A
        // when switch back, execution restarts from here
        sleep(1);  //pretends to be busy in this thread. But this actually blocks the whole process.
    }
    return NULL;
}

void* func_C()
{
    while (1) {
        printf("Thread ID[%d] is executing with stack top[%p]\n", g_thread_C.id, g_thread_C.stack_esp);
        Thread_switch(&g_thread_C, &g_thread_A);
        sleep(1);
    }
    return NULL;
}
 
int main()
{
    Thread_create_with_ID(&g_thread_A, 1, func_A);     //A is ready
    Thread_create_with_ID(&g_thread_B, 2, func_B);     //B is ready
    Thread_create_with_ID(&g_thread_C, 3, func_C);     //C is ready
 
    // schedule starts
    Thread_start_with_save(&g_thread_A);

    //never reaches here in this demo because user context will only be switched between thread A and B
    Thread_destroy(&g_thread_A);
    Thread_destroy(&g_thread_B);
    Thread_destroy(&g_thread_C);
    return 0;    
}
