/*
 * BL602 Arduino Core - Main Entry Point
 *
 * Implements the standard application main() hook invoked by
 * Bouffalo SDK's bfl_main() / app_main_entry task.
 *
 * SPDX-License-Identifier: MIT
 */

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <FreeRTOS.h>
#include <task.h>

extern void bl_uart_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin,
                         uint8_t cts_pin, uint8_t rts_pin, uint32_t baudrate);
extern int bl_uart_data_send(uint8_t id, uint8_t data);

extern void setup(void);
extern void loop(void);

static void arduino_task(void *arg)
{
    (void)arg;
    setup();

    for (;;) {
        loop();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

int main(void)
{
    /* 1. Reinitialize UART0 to 115200 baud (GPIO16=TX, GPIO7=RX) */
    bl_uart_init(0, 16, 7, 255, 255, 115200);

    /* 2. Create the Arduino main task */
    BaseType_t result = xTaskCreate(
        arduino_task,
        (char *)"arduino_task",
        2048,
        NULL,
        5,
        NULL
    );

    /* 3. Check xTaskCreate() return value */
    if (result != pdPASS) {
        /* Task creation failed - print diagnostic message and halt */
        for (;;) {
            bl_uart_init(0, 16, 7, 255, 255, 115200);
            const char err[] = "\r\n[FATAL] xTaskCreate(arduino_task) failed!\r\n";
            for (const char *p = err; *p; p++) {
                bl_uart_data_send(0, (uint8_t)*p);
            }
            for (volatile int i = 0; i < 5000000; i++);
        }
    }

    /* 4. Return 0 (app_main_entry task will delete itself, FreeRTOS continues) */
    return 0;
}

#ifdef __cplusplus
}
#endif
