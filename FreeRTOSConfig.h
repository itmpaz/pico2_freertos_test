#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* ---------------------------------------------------------------
 * FreeRTOS configuration for Raspberry Pi Pico 2 (RP2350 / Cortex-M33)
 * Modelled on the official raspberrypi/pico-examples freertos config.
 * --------------------------------------------------------------- */

#include <stdint.h>

/* Scheduler */
#define configUSE_PREEMPTION                    1
#define configUSE_TIME_SLICING                  1
#define configUSE_TICKLESS_IDLE                 0
#define configCPU_CLOCK_HZ                      150000000UL
#define configTICK_RATE_HZ                      1000
#define configTICK_TYPE_WIDTH_IN_BITS           TICK_TYPE_WIDTH_32_BITS

/* Tasks */
#define configMAX_PRIORITIES                    8
#define configMINIMAL_STACK_SIZE                256
#define configMAX_TASK_NAME_LEN                 16
#define configIDLE_SHOULD_YIELD                 1

/* Memory */
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configSUPPORT_STATIC_ALLOCATION         0
#define configTOTAL_HEAP_SIZE                   (64 * 1024)

/* Hooks */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          2
#define configUSE_MALLOC_FAILED_HOOK            1
#define configUSE_PASSIVE_IDLE_HOOK             0

/* Timers */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            1024

/* Synchronisation */
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               8

/* Debugging */
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#define configGENERATE_RUN_TIME_STATS           0

/* ---------------------------------------------------------------
 * Pico SDK interop — required by the RP2350 port.
 * configSUPPORT_PICO_SYNC_INTEROP enables the doorbell / spinlock
 * notify mechanism which calls xEventGroupSetBitsFromISR() and
 * xTimerPendFunctionCallFromISR() internally.
 * --------------------------------------------------------------- */
#define configSUPPORT_PICO_SYNC_INTEROP         1
#define configSUPPORT_PICO_TIME_INTEROP         1

/* ---------------------------------------------------------------
 * SMP — RP2350 is dual-core; the raspberrypi port is SMP-capable.
 * Set configNUMBER_OF_CORES 1 to run on a single core only.
 * --------------------------------------------------------------- */
#ifdef FREE_RTOS_KERNEL_SMP
#define configNUMBER_OF_CORES                   2
#define configNUM_CORES                         configNUMBER_OF_CORES
#define configTICK_CORE                         0
#define configRUN_MULTIPLE_PRIORITIES           1
#if configNUMBER_OF_CORES > 1
#define configUSE_CORE_AFFINITY                 1
#endif
#endif

/* ---------------------------------------------------------------
 * Cortex-M33 / RP2350 specific — all required by the port
 * --------------------------------------------------------------- */
#define configENABLE_FPU                        1
#define configENABLE_MPU                        0
#define configENABLE_TRUSTZONE                  0
#define configRUN_FREERTOS_SECURE_ONLY          1   /* NTZ = run entirely in secure/non-TZ mode */

/* Interrupt priorities */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    16

/* Assert */
#include <assert.h>
#define configASSERT( x )                       assert( x )

/* ---------------------------------------------------------------
 * Optional API
 * --------------------------------------------------------------- */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_xTaskGetIdleTaskHandle          1
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_xTaskAbortDelay                 1
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_xTaskResumeFromISR              1
#define INCLUDE_xQueueGetMutexHolder            1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_pcTaskGetTaskName               1

#endif /* FREERTOS_CONFIG_H */