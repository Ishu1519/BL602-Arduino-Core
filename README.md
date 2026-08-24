# BL602 Arduino Core

Arduino core for **Bouffalo Lab BL602** — a RISC-V (RV32IMFC) MCU with integrated Wi-Fi and Bluetooth LE.

This core provides a familiar Arduino programming interface for the BL602, built on top of the Bouffalo SDK with FreeRTOS.

> **Version 0.1.0** — Early release. Core GPIO, Serial, and WiFi functionality have been physically tested on real hardware. See the feature matrix below for details.

## Features

| Feature | Status | Notes |
|---------|--------|-------|
| Arduino `setup()` / `loop()` | ✅ Tested | Runs in FreeRTOS task |
| `Serial` @ 115200 baud | ✅ Tested | UART0: GPIO16 TX, GPIO7 RX |
| `pinMode` / `digitalWrite` / `digitalRead` | ✅ Tested | Selected pins physically tested |
| `delay()` / `millis()` / `micros()` | ✅ Tested | FreeRTOS tick-based |
| `yield()` | ✅ Tested | FreeRTOS `taskYIELD()` |
| `Print` / `println` | ✅ Tested | Full Print class |
| `String` (WString) | ✅ Tested | Basic String operations |
| Native SDK WiFi (AP/HTTP) | ✅ Tested | Physically tested via native SDK |
| Arduino WiFi API | ❌ Not verified | Moved to experimental/ |
| I2C / Wire | ⚠️ Experimental | Implemented, not physically verified |
| Native BLE Advertising | ✅ Tested | Physically tested separately |
| Arduino BLE API | ❌ Not supported | Unsupported/Experimental |
| WiFi + BLE Coexistence | ❌ Unverified | Not proven |
| Analog I/O / PWM | ❌ Not implemented | |
| SPI | ❌ Not implemented | |
| Arduino IDE Compile | ❌ Unverified | Requires SDK build system |

## Supported Boards

- **Bouffalo Lab BL602** — RISC-V RV32IMFC, 160 MHz, 276 KB SRAM, 2 MB Flash
  - Ai-Thinker Ai-WB2 modules
  - Pine64 PineCone
  - DT-BL10
  - Any BL602-based board with UART0 access

## Installation

### Option A: Manual Installation from GitHub

```bash
git clone https://github.com/Ishu1519/BL602-Arduino-Core.git
```

See [docs/building-from-source.md](docs/building-from-source.md) for build instructions using the Bouffalo SDK.

### Option B: Arduino IDE Boards Manager (Future)

> **Note**: Boards Manager packaging prepared; first release package pending.

When available, add this URL to **File → Preferences → Additional Boards Manager URLs**:

```
https://raw.githubusercontent.com/Ishu1519/BL602-Arduino-Core/main/package_bl602_index.json
```

Then search for **BL602** in Boards Manager.

## First Example

```cpp
#include <Arduino.h>
#include <HardwareSerial.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Hello from BL602!");
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    Serial.println("BL602 alive");
}
```

## Pin Mapping

Pin numbers map directly to BL602 GPIO numbers. There is no remapping.

| Function | GPIO | Notes |
|----------|------|-------|
| Serial TX | GPIO16 | UART0 |
| Serial RX | GPIO7 | UART0 |
| LED_BUILTIN | GPIO1 | Board-dependent |
| I2C SDA | GPIO4 | Experimental |
| I2C SCL | GPIO3 | Experimental |
| BOOT | GPIO8 | Hold HIGH for bootloader |

See [docs/pin-mapping.md](docs/pin-mapping.md) for the full pin table.

## Serial

This core initializes UART0 at **115200 baud** on startup:

```c
bl_uart_init(0, 16, 7, 255, 255, 115200);
```

**Important**: The BL602 SDK default console uses 2,000,000 baud, which most USB-TTL adapters cannot reliably decode. This Arduino core explicitly overrides UART0 to 115200 baud so standard serial terminals work correctly.

Connect your USB-TTL adapter:
- **GPIO16** → RX on adapter
- **GPIO7** → TX on adapter
- **GND** → GND

## GPIO

```cpp
pinMode(5, OUTPUT);
digitalWrite(5, HIGH);

pinMode(4, INPUT_PULLUP);
int val = digitalRead(4);
```

Supported modes: `INPUT`, `OUTPUT`, `INPUT_PULLUP`, `INPUT_PULLDOWN`.

## WiFi

WiFi has been physically verified in Access Point mode. The BL602 creates a WiFi network and serves HTTP responses at 192.168.4.1.

WiFi requires the full SDK build system — it is not available through the Arduino IDE compile button. See [docs/building-from-source.md](docs/building-from-source.md).

## BLE (Experimental)

Native BLE advertising has been physically verified on BL602 using the Bouffalo BLE stack. The device was detected by nRF Connect.

**What works:**
- BLE advertisement using native SDK APIs
- Device visible on BLE scanners

**What is NOT validated:**
- Arduino BLE API (not implemented)
- WiFi + BLE simultaneous operation (experimental)
- GATT services / characteristics

See `examples/05.BLE/NativeBLEAdvertise/` for details.

## Building from Source

This core requires the Bouffalo BL602 SDK build system:

```bash
# Clone the SDK
git clone https://github.com/bouffalolab/bl_iot_sdk.git ~/OpenBL602

# Create your project under customer_app/
cd ~/OpenBL602/customer_app/my_project

# Build
make CONFIG_CHIP_NAME=BL602 -j$(nproc)
```

See [docs/building-from-source.md](docs/building-from-source.md) for complete instructions.

## Uploading Firmware

1. Put BL602 in bootloader mode (hold GPIO8/BOOT HIGH, press RESET, release BOOT)
2. Flash:
   ```bash
   bflb_iot_tool --chipname=bl602 --interface=uart \
       --port=/dev/ttyUSB0 --baudrate=115200 \
       --firmware=build_out/bl602_demo_wifi.bin
   ```
3. Press RESET to run the firmware

## Known Limitations

- **No Arduino IDE compilation yet** — The core/runtime implementation is working and Arduino-style APIs are implemented, but the current project build still relies on the Bouffalo SDK. Arduino IDE direct compile/upload has NOT yet been physically validated.
- **No analog I/O** — `analogRead()` and `analogWrite()` are not implemented.
- **No SPI** — SPI library is not implemented.
- **Wire/I2C is untested** — The library compiles but has not been verified on hardware.
- **BLE is experimental** — Only native SDK BLE advertising has been tested. No Arduino BLE API.
- **Single-threaded Arduino** — `setup()`/`loop()` run in one FreeRTOS task. WiFi and BLE run in separate SDK tasks.

## Troubleshooting

See [docs/troubleshooting.md](docs/troubleshooting.md) for common issues and solutions.

## Contributing

Contributions are welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

Areas where help is especially needed:
- Arduino IDE compilation support
- Analog I/O and PWM implementation
- SPI library
- I2C/Wire physical verification
- Additional board variants

## License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE).

## Third-Party Notices

This project uses components from:
- **Bouffalo Lab BL602 SDK** (Apache 2.0 / BSD-3-Clause)
- **FreeRTOS** (MIT)
- **lwIP** (BSD-3-Clause)

See [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md) for full details.

## Credits

- [Bouffalo Lab](https://www.bouffalolab.com/) for the BL602 SDK
- [Arduino](https://www.arduino.cc/) for the Arduino platform specification
- The open-source BL602 community
