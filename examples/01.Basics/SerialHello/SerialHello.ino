/*
 * BL602 Arduino Serial Hello Example
 *
 * Prints a greeting over UART0 at 115200 baud.
 * Connect a USB-TTL adapter to GPIO16 (TX) and GPIO7 (RX).
 */

#include <Arduino.h>
#include <HardwareSerial.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Hello from BL602!");
}

void loop() {
    Serial.println("BL602 alive");
    delay(1000);
}
