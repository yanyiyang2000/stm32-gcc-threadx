#include <stdint.h>

#include "stm32l476xx.h"

#include "tx_api.h"

#include "clock_config.h"
#include "gpio_config.h"

#define STACK_SIZE     	1024
#define BYTE_POOL_SIZE	9120
#define BLOCK_POOL_SIZE 100

extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __heap_start__;
extern uint32_t __heap_end__;
extern uint32_t __stack_start__;
extern uint32_t __stack_end__;

TX_BYTE_POOL byte_pool_0;
UCHAR        memory_area[BYTE_POOL_SIZE];

/* Define the ThreadX object control blocks.  */
TX_THREAD thread_1;
TX_THREAD thread_2;
TX_MUTEX  mutex_0;

/* Define thread prototypes.  */
void thread_1_entry(ULONG thread_input);
void thread_2_entry(ULONG thread_input);


int main() {
    MSI_config();
    GPIO_PA5_config();

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}


void tx_application_define(void *first_unused_memory) {
    CHAR *pointer = TX_NULL;

    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", memory_area, BYTE_POOL_SIZE);

    /* Allocate the stack for thread 1.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);

    /* Create threads 1 and 2. These threads compete for a ThreadX mutex.  */
    tx_thread_create(&thread_1, "thread 1", thread_1_entry, 1,
                        pointer, STACK_SIZE,
                        8, 8, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Allocate the stack for thread 2.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&thread_2, "thread 2", thread_2_entry, 2,
                        pointer, STACK_SIZE,
                        8, 8, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Create the mutex used by thread 1 and 2 without priority inheritance.  */
    tx_mutex_create(&mutex_0, "mutex 0", TX_NO_INHERIT);
}


void thread_1_entry(ULONG thread_input) {
    UINT status;

    while (1) {
        /* Get the mutex with suspension.  */
        status = tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

        /* Check status.  */
        if (status != TX_SUCCESS)
            break;

        /* Critical section start */
        GPIOA->ODR |= 1 << GPIO_ODR_OD5_Pos; // turn on LED
        /* Critical section end */

        /* Sleep for 100 ticks (1 second) to hold the mutex.  */
        tx_thread_sleep(100);

        /* Release the mutex.  */
        status = tx_mutex_put(&mutex_0);

        /* Check status.  */
        if (status != TX_SUCCESS)
            break;
    }
}


void thread_2_entry(ULONG thread_input) {
    UINT status;

    while (1) {
        /* Get the mutex with suspension.  */
        status = tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

        /* Check status.  */
        if (status != TX_SUCCESS)
            break;

        /* Critical section start */
        GPIOA->ODR &= 0 << GPIO_ODR_OD5_Pos; // turn off LED
        /* Critical section end */

        /* Sleep for 100 ticks (1 second) to hold the mutex.  */
        tx_thread_sleep(100);

        /* Release the mutex.  */
        status = tx_mutex_put(&mutex_0);

        /* Check status.  */
        if (status != TX_SUCCESS)
            break;
    }
}