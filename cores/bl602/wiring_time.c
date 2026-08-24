#include "Arduino.h"
#include <FreeRTOS.h>
#include <task.h>

unsigned long millis(void)
{
    return (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

unsigned long micros(void)
{
    return (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS * 1000);
}

void delay(unsigned long ms)
{
    if (ms == 0) return;
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void delayMicroseconds(unsigned int us)
{
    if (us == 0) return;
    volatile uint32_t count = (us * 40) / 3;
    while (count--) {
        __asm__ volatile ("nop");
    }
}

void yield(void)
{
    taskYIELD();
}
