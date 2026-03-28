#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <string.h>


//Required hooks

//configCHECK_FOR_STACK_OVERFLOW
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void) xTask;
    (void) pcTaskName;
  
    for (;;);
}

//configUSE_MALLOC_FAILED_HOOK
void vApplicationMallocFailedHook(void)
{
    /* Replace with your own error handler if needed */
    for (;;);
}




// https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/02-Queues-mutexes-and-semaphores/01-Queues

QueueHandle_t _queue;

typedef struct 
{
    char text[50];


} vSomeData;


//Blink task
void vBlinkTask(void *pvParameters)
{
    (void) pvParameters;

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    bool led_state= true;
    for (;;)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, led_state);
        vSomeData data = { 0 };
        strcpy(data.text, led_state ? "Led ON" : "Led OFF");
        xQueueSend(_queue, &data, 0);
        led_state = !led_state;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

//Hello task
void vHelloTask(void *pvParameters)
{
    (void) pvParameters;

    for (;;)
    {
        vSomeData data;
        if(xQueueReceive(_queue, &data,  portMAX_DELAY) == pdPASS)
        {
            printf("%s\n",data.text);
        }

    }
}

int main()
{
    stdio_init_all();

    _queue = xQueueCreate(1, sizeof(vSomeData));

    xTaskCreate(vBlinkTask, "Blink", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vHelloTask, "Hello", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();  

    for (;;);
}