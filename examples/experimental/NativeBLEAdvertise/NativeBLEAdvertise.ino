/*
 * BL602 Native BLE Advertising Example (EXPERIMENTAL)
 *
 * WARNING: This is an EXPERIMENTAL example using the native
 * Bouffalo BLE SDK. It has been physically verified to advertise
 * on nRF Connect, but:
 *   - Arduino BLE API is NOT implemented
 *   - WiFi + BLE coexistence is NOT fully validated
 *   - This requires the SDK build system
 *
 * The native BLE initialization sequence is:
 *   1. ble_controller_init(configMAX_PRIORITIES - 1)
 *   2. hci_driver_init()
 *   3. bt_enable(callback)
 *   4. bt_set_name("BL602-SDK-BLE")
 *   5. bt_le_adv_start(...)
 *
 * See the SDK project bl602_native_ble_sdk_test for the
 * complete working implementation.
 */

#include <Arduino.h>
#include <HardwareSerial.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Native BLE Advertise Example");
    Serial.println("EXPERIMENTAL - Requires SDK build system");
    Serial.println("See: bl602_native_ble_sdk_test/");
}

void loop() {
    delay(5000);
}
