# Troubleshooting

## Serial Output Shows Garbage Characters

**Cause**: The BL602 SDK default console runs at 2,000,000 baud.

**Solution**: This Arduino core sets UART0 to 115200 baud at startup.
Make sure your serial terminal is set to **115200 baud**.

If you still see garbage, verify:
- TX/RX wires are not swapped
- USB-TTL adapter supports 3.3V logic levels
- Correct COM port / `/dev/ttyUSB0` is selected

## Build Fails: "No such file or directory: bl_uart.h"

**Cause**: Missing `CONFIG_CHIP_NAME` in the build.

**Solution**: Build with:
```bash
make CONFIG_CHIP_NAME=BL602 -j$(nproc)
```

## Cannot Flash: Device Not Responding

1. **Enter bootloader mode**: Hold BOOT (GPIO8 HIGH), press RESET, release BOOT
2. **Check port**: Verify the correct serial port
3. **Try lower baud rate**: Use `--baudrate=115200` instead of 2000000

## WiFi AP Not Appearing

1. Verify the firmware was built with WiFi components enabled
2. Check that `CONFIG_BL_IOT_FW_AP:=1` is set in `proj_config.mk`
3. The default AP SSID is "BL602_Motor_Setup" (configurable)

## BLE Not Working

BLE support is **experimental**. Requirements:
- `CONFIG_BT:=1` in `proj_config.mk`
- `CONFIG_LINK_ROM:=1` in `proj_config.mk`
- Build with `CONFIG_CHIP_NAME=BL602`
- BLE initialization must happen after WiFi AP starts

## FreeRTOS Stack Overflow

If the firmware crashes or reboots unexpectedly:
- Increase the Arduino task stack size in `main.cpp` (default: 2048 words)
- Check for large local variables in `setup()` or `loop()`
