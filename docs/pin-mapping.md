# BL602 Pin Mapping

## GPIO Pin Table

| Arduino Pin | BL602 GPIO | Default Function | Notes |
|-------------|-----------|-------------------|-------|
| 0           | GPIO0     | General I/O       | |
| 1           | GPIO1     | LED_BUILTIN       | On-board LED on some boards |
| 2           | GPIO2     | General I/O       | |
| 3           | GPIO3     | I2C SCL / SPI SCK | Default Wire SCL |
| 4           | GPIO4     | I2C SDA / SPI SS  | Default Wire SDA |
| 5           | GPIO5     | General I/O       | |
| 7           | GPIO7     | UART0 RX          | Serial RX |
| 8           | GPIO8     | BOOT pin          | Hold HIGH for bootloader |
| 11          | GPIO11    | General I/O       | |
| 12          | GPIO12    | General I/O       | |
| 14          | GPIO14    | General I/O       | |
| 16          | GPIO16    | UART0 TX          | Serial TX |
| 17          | GPIO17    | General I/O       | |

## UART0 (Serial)

| Function | Pin    |
|----------|--------|
| TX       | GPIO16 |
| RX       | GPIO7  |
| Baud     | 115200 (default) |

## I2C (Wire) — Experimental

| Function | Pin   |
|----------|-------|
| SDA      | GPIO4 |
| SCL      | GPIO3 |

## Notes

- BL602 has 32 GPIO pins (GPIO0-GPIO31), but not all are available
  on every development board
- GPIO8 is the BOOT pin — hold HIGH during reset to enter bootloader
- Pin numbers in Arduino code map directly to BL602 GPIO numbers
- There is no pin remapping — `pinMode(5, OUTPUT)` controls GPIO5
