# BL602 UART Configuration & Baud Rate Diagnosis

## Technical Background

The Bouffalo Lab BL602 microcontroller includes two UART peripherals (UART0 and UART1). In the default Bouffalo SDK (`bl_iot_sdk`), the early bootloader and system console are preconfigured to **2,000,000 baud (2 Mbaud)**:

```c
/* Standard Bouffalo SDK default console configuration */
#define BFLB_CONSOLE_UART_BAUD  (2000000)
```

While 2 Mbaud offers rapid debug logging during high-throughput RF testing, it introduces major real-world friction for typical embedded development:
1. Most generic USB-to-UART bridge ICs (e.g. standard CP2102, CH340G, FT232R) fail to sample reliably or produce high clock divisor jitter at 2.0 MBaud.
2. Standard Arduino IDE Serial Monitors and embedded terminal emulators default to **115,200 baud**.
3. Connecting at 115200 to a 2 Mbaud console outputs unreadable framing errors and garbage bytes (`\xff\xfc...`).

## Verified Solution in Arduino Core

In the BL602 Arduino Core, the application startup sequence explicitly reinitializes UART0 to **115,200 baud (8-N-1)** immediately when `main()` takes control after the FreeRTOS scheduler starts:

```c
/* cores/bl602/main.cpp */
bl_uart_init(0, 16, 7, 255, 255, 115200);
```

### Pin Assignment
* **UART0 TX**: `GPIO 16`
* **UART0 RX**: `GPIO 7`
* **Hardware Flow Control (CTS/RTS)**: Disabled (`255`, `255`)
* **Baud Rate**: `115200`

## Terminal Configuration

When connecting your serial terminal (Arduino Serial Monitor, PuTTY, minicom, picocom):

* **Port**: Select your USB-to-TTL COM port (e.g. `COM7` on Windows, `/dev/ttyUSB0` on Linux)
* **Baud Rate**: `115200`
* **Data Bits**: `8`
* **Parity**: `None`
* **Stop Bits**: `1`
* **Flow Control**: `None`

## Physical Evidence

Upon physical reset of the BL602C40 SoC, the Arduino core outputs:
```text
ARDUINO CLI BL602 BOOT OK
ARDUINO CLI ALIVE
ARDUINO CLI ALIVE
```
