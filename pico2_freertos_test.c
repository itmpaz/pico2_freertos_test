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
    /* Replace with your own error handler if needed */
    for (;;);
}


//Blink task
void vBlinkTask(void *pvParameters)
{
    (void) pvParameters;

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    for (;;)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        vTaskDelay(pdMS_TO_TICKS(300));
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        vTaskDelay(pdMS_TO_TICKS(300));
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

    xTaskCreate(vBlinkTask, "Blink", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vHelloTask, "Hello", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();  

    for (;;);
}