#include "Arduino.h"
#include "bl_gpio.h"
#include "bl602_glb.h"

void pinMode(uint8_t pin, uint8_t mode)
{
    if (pin > 31) return;

    if (mode == OUTPUT) {
        bl_gpio_enable_output(pin, 0, 0);
        GLB_GPIO_INPUT_Enable((GLB_GPIO_Type)pin);
    } else if (mode == INPUT) {
        bl_gpio_enable_input(pin, 0, 0);
    } else if (mode == INPUT_PULLUP) {
        bl_gpio_enable_input(pin, 1, 0);
    } else if (mode == INPUT_PULLDOWN) {
        bl_gpio_enable_input(pin, 0, 1);
    }
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    if (pin > 31) return;
    bl_gpio_output_set(pin, val ? 1 : 0);
}

int digitalRead(uint8_t pin)
{
    if (pin > 31) return 0;
    uint8_t val = 0;
    bl_gpio_input_get(pin, &val);
    return val ? HIGH : LOW;
}
