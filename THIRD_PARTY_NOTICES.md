# Third-Party Notices

This project incorporates or references code from the following third-party
projects. Their respective licenses are preserved below.

---

## Bouffalo Lab BL602 SDK (OpenBL602)

**License**: Apache License 2.0

The BL602 SDK provides the hardware abstraction layer, WiFi firmware, BLE
stack, and FreeRTOS integration used by this Arduino core. Some SDK component
files (e.g., `coex_debug.c`, `wifi_prov_api.c`) use a BSD-3-Clause license
as noted in their file headers.

- Repository: https://github.com/bouffalolab/bl_iot_sdk
- SPDX: Apache-2.0 AND BSD-3-Clause

---

## FreeRTOS

**License**: MIT

This Arduino core runs the Arduino `setup()`/`loop()` cycle inside a
FreeRTOS task. FreeRTOS is bundled as part of the Bouffalo SDK.

- Website: https://www.freertos.org/
- SPDX: MIT

---

## lwIP (Lightweight IP)

**License**: BSD-3-Clause

The WiFi networking and HTTP server functionality uses lwIP sockets,
which is included in the Bouffalo SDK.

- Website: https://savannah.nongnu.org/projects/lwip/
- SPDX: BSD-3-Clause

---

## Arduino Core API

**License**: LGPL-2.1-or-later

The Arduino API definitions (`setup()`, `loop()`, `pinMode()`,
`digitalWrite()`, `Serial`, `Print`, `Stream`, `String`, etc.) are based
on the Arduino platform specification. Our implementations are original
code written for the BL602 platform, but follow the API contract defined
by the Arduino project.

- Website: https://www.arduino.cc/
- SPDX: LGPL-2.1-or-later
