/*
 * BL602 Arduino GPIO Example
 *
 * Toggles GPIO5 as output, reads GPIO4 as input.
 * Prints the input state over Serial.
 */

#include <Arduino.h>
#include <HardwareSerial.h>

#define OUTPUT_PIN  5
#define INPUT_PIN   4

void setup() {
    Serial.begin(115200);
    pinMode(OUTPUT_PIN, OUTPUT);
    pinMode(INPUT_PIN, INPUT_PULLUP);
    Serial.println("GPIO test started");
}

void loop() {
    digitalWrite(OUTPUT_PIN, HIGH);
    delay(500);
    int val = digitalRead(INPUT_PIN);
    Serial.print("Input pin: ");
    Serial.println(val);

    digitalWrite(OUTPUT_PIN, LOW);
    delay(500);
}
