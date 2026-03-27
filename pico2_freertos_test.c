#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"


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
    for (;;);
}



typedef struct {
    uint pin;
    uint delay;
} vBlinkTaskParams;

//Blink task
void vBlinkTask(void *pvParameters)
{
    vBlinkTaskParams *p =  (vBlinkTaskParams*)pvParameters;

    gpio_init(p->pin);
    gpio_set_dir(p->pin, GPIO_OUT);

    for (;;)
    {
        gpio_put(p->pin, true);
        vTaskDelay(pdMS_TO_TICKS(p->delay));
        gpio_put(p->pin, false);
        vTaskDelay(pdMS_TO_TICKS(p->delay));
    }
}

//Hello task
void vHelloTask(void *pvParameters)
{
    (void) pvParameters;

    for (;;)
    {
        printf("Hello from FreeRTOS on Pico 2!\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int main()
{
    stdio_init_all();
    vBlinkTaskParams p1 = { 14, 300 };
    vBlinkTaskParams p2 = { 17, 600 };

    xTaskCreate(vBlinkTask, "Blink", 256, &p1, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vBlinkTask, "Blink", 256, &p2, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vHelloTask, "Hello", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();  

    for (;;);
}