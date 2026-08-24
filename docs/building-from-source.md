# Building from Source

## Prerequisites

- Linux (Ubuntu 20.04+ recommended, or WSL2 on Windows)
- Bouffalo Lab BL602 SDK (`bl_iot_sdk` / `OpenBL602`)
- RISC-V GCC toolchain (included in the SDK)

## SDK Setup

1. Clone the Bouffalo SDK:
   ```bash
   git clone https://github.com/bouffalolab/bl_iot_sdk.git ~/OpenBL602
   ```

2. The SDK includes the RISC-V toolchain in `toolchain/riscv/`.

## Project Structure

A BL602 Arduino project lives under `customer_app/` in the SDK tree:

```
~/OpenBL602/customer_app/my_project/
├── Makefile
├── proj_config.mk
└── bl602_demo_wifi/          # Source directory
    ├── main.c                # SDK entry + WiFi runtime
    ├── arduino_test.cpp      # Your Arduino sketch
    ├── Arduino.h
    ├── HardwareSerial.cpp/h
    ├── Print.cpp/h
    ├── Stream.h
    ├── WString.cpp/h
    ├── wiring_digital.c
    ├── wiring_time.c
    └── bouffalo.mk
```

## Build Commands

```bash
cd ~/OpenBL602/customer_app/my_project
make CONFIG_CHIP_NAME=BL602 -j$(nproc)
```

The output binary is at:
```
build_out/bl602_demo_wifi.bin
```

## Flash the Firmware

1. Put BL602 in bootloader mode (hold BOOT/GPIO8 HIGH, press RESET)
2. Flash:
   ```bash
   bflb_iot_tool --chipname=bl602 --interface=uart \
       --port=/dev/ttyUSB0 --baudrate=115200 \
       --firmware=build_out/bl602_demo_wifi.bin
   ```
3. Press RESET to run

## Verify

Open a serial terminal at 115200 baud:
```bash
picocom -b 115200 /dev/ttyUSB0
```

You should see Arduino `Serial.println()` output.
