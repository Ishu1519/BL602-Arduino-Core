/*
 * BL602 Arduino Blink Without Delay
 *
 * Toggles LED_BUILTIN (GPIO1) using millis() instead of delay().
 */

#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 500;
int ledState = LOW;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        ledState = (ledState == LOW) ? HIGH : LOW;
        digitalWrite(LED_BUILTIN, ledState);
    }
}
