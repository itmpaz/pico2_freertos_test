#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


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
    char text[100];
    uint delay;
} vHelloTaskParams;


SemaphoreHandle_t _xSemaphore;


//Hello task
void vHelloTask(void *pvParameters)
{
    vHelloTaskParams *p =  (vHelloTaskParams*)pvParameters;

    for (;;)
    {
        uint pos=0;
        if(xSemaphoreTake(_xSemaphore, portMAX_DELAY) == pdTRUE) 
        {
            while(p->text[pos]!=0)
            {
                printf("%c",p->text[pos++]);
                for(uint i=0;i<1000000;i++) ;
                //vTaskDelay(100);
            }

            xSemaphoreGive(_xSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(p->delay));
        //for(uint i=0;i<p->delay*10000;i++) ;
        
    }
}

int main()
{
    stdio_init_all();


    _xSemaphore = xSemaphoreCreateMutex();

    assert( _xSemaphore != NULL );


    vHelloTaskParams t1 = { "11111111111\n", 1000 };
    vHelloTaskParams t2 = { "22222222222\n", 2000 };

    xTaskCreate(vHelloTask, "Hello1", 256, &t1, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vHelloTask, "Hello2", 256, &t2, tskIDLE_PRIORITY + 2, NULL);

    vTaskStartScheduler();  

    for (;;);
}