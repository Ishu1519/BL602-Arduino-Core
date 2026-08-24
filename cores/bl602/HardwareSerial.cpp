#include "HardwareSerial.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "bl_uart.h"
#ifdef __cplusplus
}
#endif

HardwareSerial Serial(0);

HardwareSerial::HardwareSerial(uint8_t uart_id) : _uart_id(uart_id)
{
}

void HardwareSerial::begin(unsigned long baud)
{
    if (_uart_id == 0) {
        bl_uart_init(0, 16, 7, 255, 255, (uint32_t)baud);
    }
}

void HardwareSerial::end()
{
}

int HardwareSerial::available()
{
    return 0;
}

int HardwareSerial::peek()
{
    return -1;
}

int HardwareSerial::read()
{
    return bl_uart_data_recv(_uart_id);
}

void HardwareSerial::flush()
{
    bl_uart_flush(_uart_id);
}

size_t HardwareSerial::write(uint8_t c)
{
    bl_uart_data_send(_uart_id, c);
    return 1;
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
{
    if (!buffer || size == 0) return 0;
    for (size_t i = 0; i < size; i++) {
        bl_uart_data_send(_uart_id, buffer[i]);
    }
    return size;
}
