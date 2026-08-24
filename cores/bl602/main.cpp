/*
 * BL602 Arduino Core - Main Entry Point
 *
 * Initializes UART0 at 115200 baud on GPIO16 (TX) / GPIO7 (RX),
 * then runs the Arduino setup()/loop() cycle in a FreeRTOS task.
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
    /* Initialize UART0 at 115200 baud (GPIO16=TX, GPIO7=RX) */
    bl_uart_init(0, 16, 7, 255, 255, 115200);

    xTaskCreate(
        arduino_task,
        (char *)"arduino_task",
        2048,
        NULL,
        5,
        NULL
    );

    return 0;
}

#ifdef __cplusplus
}
#endif
