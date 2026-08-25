# BL602 SPI Flash Tool Debugging & Resolution

## Problem Statement

During initial automated upload tests using the `bflb_iot_tool` package, the flashing sequence aborted during flash identification with the following error:

```text
[01:15:37.179] - flash set para
[01:15:37.179] - ========= flash read jedec ID =========
[01:15:37.182] - Read flash jedec ID
[01:15:37.182] - readdata:
[01:15:37.182] - b'c8401680'
[01:15:37.182] - Finished
[01:15:37.183] - {"ErrorCode": "003D","ErrorMsg":"BFLB FLASH MATCH TYPE FAIL"}
[01:15:37.183] - Burn return with retry fail
```

## Root Cause Analysis

### 1. Flash Chip Identification
Querying the SPI NOR flash with standard JEDEC command `0x9F` (RDID) returned the 4-byte response `0xC8 0x40 0x16 0x80`:

| Byte | Value | Meaning |
| :--- | :--- | :--- |
| **0** | `0xC8` | **Manufacturer ID**: GigaDevice Semiconductor |
| **1** | `0x40` | **Memory Type**: SPI NOR Flash (3.3V) |
| **2** | `0x16` | **Capacity / Density Code**: 32 Megabits (4 Megabytes) |
| **3** | `0x80` | **Extended Device Information (EDI)** |

In standard JEDEC SPI flash density encoding (JESD216 / RDID), the capacity code `0x16` represents a 32-Mbit (4-Mbyte) NOR flash array ($2^{22}$ bytes / $2^{25}$ bits). This corresponds directly to the GigaDevice `GD25Q32C` / `GD25Q32E` series used on the Ai-WB2-M1-I module. The Ai-WB2-M1-I module uses a GigaDevice 4 MB SPI NOR flash device.

### 2. Discrepancy in Tool Bundling
* **Legacy Helper Binary**: The initial tool package bundled `eflash_loader_v2.4.2` (`37,344 bytes`, SHA256: `07712B07...`) from the older `OpenBL602` tree. Its on-chip lookup table failed to match the 4-byte JEDEC return without an external configuration table.
* **Missing Flash Database**: The package omitted the `utils/flash/bl602/` directory containing the vendor `.conf` profiles.

## Engineering Fix

1. **Updated Loader Binary**: Replaced all loader helper binaries with `eflash_loader_v2.5.1` (`38,784 bytes`, SHA256: `2AA46589...`) from BouffaloLabDevCube v1.9.0.
2. **Bundled Flash Configuration Database**: Integrated the `utils/flash/bl602/` directory containing the BL602 flash parameter database, including `GD25Q32C_c84016.conf` and `flashcfg_list.csv`.
3. **Corrected Platform Upload Arguments**: Formatted the `--firmware` argument in `platform.txt` to `"--firmware={build.path}/{build.project_name}.bin"` so that Python `argparse` reliably parses the path without embedded quotes.

## Physical Verification Evidence

With `v0.1.0-alpha.3`, upload executes cleanly to completion:

```text
[bflb_iot_tool] Version: eflash_loader_v2.5.1
[bflb_iot_tool] flash jedec id: c8401680
[bflb_iot_tool] get flash size: 0x00400000 (4 MB)
[bflb_iot_tool] ========= programming chips\bl602\partition\partition.bin to 0x0000E000
[bflb_iot_tool] Sha caled by host: fd6af18fc4aaf2807277cac767ca19d12af7b55f5ecbb8902ef28bc2430524aa
[bflb_iot_tool] Sha caled by dev:  fd6af18fc4aaf2807277cac767ca19d12af7b55f5ecbb8902ef28bc2430524aa
[bflb_iot_tool] Verify success
[bflb_iot_tool] ========= programming chips\bl602\partition\partition.bin to 0x0000F000
[bflb_iot_tool] Verify success
[bflb_iot_tool] Program Finished
[bflb_iot_tool] [All Success]
```
