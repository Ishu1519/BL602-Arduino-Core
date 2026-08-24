# Getting Started with BL602 Arduino Core

## What You Need

- **BL602 development board** (e.g., Ai-Thinker Ai-WB2, Pine64 PineCone, DT-BL10)
- **USB-to-TTL serial adapter** (CP2102, CH340, FTDI, etc.)
- **Linux environment** (native or WSL2 on Windows)

## Hardware Connections

| Signal | BL602 Pin | Description |
|--------|-----------|-------------|
| TX     | GPIO16    | UART0 transmit |
| RX     | GPIO7     | UART0 receive |
| GND    | GND       | Common ground |
| 3V3    | 3V3       | Power supply |

## Quick Start

1. Clone the repository:
   ```bash
   git clone https://github.com/Ishu1519/BL602-Arduino-Core.git
   ```

2. Set up the Bouffalo SDK (see [building-from-source.md](building-from-source.md))

3. Write your Arduino sketch in the project's `main.c` or `arduino_test.cpp`

4. Build with `make`

5. Flash using `bflb_iot_tool`

6. Open a serial terminal at **115200 baud** to see output

## Important: UART Baud Rate

The BL602 SDK default console uses **2,000,000 baud**, which most USB-TTL
adapters cannot decode reliably. This Arduino core explicitly initializes
UART0 to **115200 baud** at startup:

```c
bl_uart_init(0, 16, 7, 255, 255, 115200);
```

Always set your serial terminal to **115200** baud.
