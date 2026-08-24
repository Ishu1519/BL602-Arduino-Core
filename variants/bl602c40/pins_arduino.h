#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define NUM_DIGITAL_PINS        (32)
#define NUM_ANALOG_INPUTS       (6)

/* Default On-Board LEDs / Buttons */
#define LED_BUILTIN             (1)

/* UART0 Pins */
#define PIN_SERIAL_TX           (16)
#define PIN_SERIAL_RX           (7)

/* Default I2C Pins */
#define PIN_WIRE_SDA            (4)
#define PIN_WIRE_SCL            (3)

/* Default SPI Pins */
#define PIN_SPI_MOSI            (1)
#define PIN_SPI_MISO            (2)
#define PIN_SPI_SCK             (3)
#define PIN_SPI_SS              (4)

#endif /* Pins_Arduino_h */
