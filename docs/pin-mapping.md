# BL602 Pin Mapping

## GPIO Pin Table

| Arduino Pin | BL602 GPIO | Default Function | Notes |
|:---:|:---:|:---|:---|
| `0` | GPIO 0 | General I/O | |
| `1` | GPIO 1 | General I/O / Test Pin | Verified test pin (tested with external LED/meter) |
| `2` | GPIO 2 | General I/O | |
| `3` | GPIO 3 | I2C SCL | Default Wire SCL (Experimental) |
| `4` | GPIO 4 | I2C SDA | Default Wire SDA (Experimental) |
| `5` | GPIO 5 | General I/O | |
| `7` | GPIO 7 | UART0 RX | Serial RX (115200 baud) |
| `8` | GPIO 8 | BOOT pin | Hold HIGH during reset to enter bootloader |
| `11` | GPIO 11 | General I/O | |
| `12` | GPIO 12 | General I/O | |
| `14` | GPIO 14 | General I/O | |
| `16` | GPIO 16 | UART0 TX | Serial TX (115200 baud) |
| `17` | GPIO 17 | General I/O | |

## UART0 (Serial)

| Function | Pin | Notes |
|:---|:---:|:---|
| **TX** | GPIO 16 | Connect to USB-TTL RX |
| **RX** | GPIO 7 | Connect to USB-TTL TX |
| **Baud** | `115200` | Configured automatically on startup |

## I2C (Wire) — Experimental

| Function | Pin |
|:---|:---:|
| **SDA** | GPIO 4 |
| **SCL** | GPIO 3 |

## Hardware Notes

- BL602 has up to 32 GPIO pins (GPIO 0–31), though breakout depends on the specific module package.
- **BOOT Mode**: GPIO 8 is the boot configuration pin. Pull HIGH (3.3V) during reset to enter UART flashing mode.
- Pin numbers in Arduino code map directly 1:1 to BL602 GPIO numbers (e.g., `pinMode(1, OUTPUT)` configures GPIO 1).
- **LED_BUILTIN**: The tested Ai-Thinker Ai-WB2-M1-I module does not feature an onboard user LED. Do not rely on `LED_BUILTIN`. Connect an external LED with a current-limiting resistor to GPIO 1 for testing.
