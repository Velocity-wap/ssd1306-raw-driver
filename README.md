# SSD1306 Raw Driver

Bare-metal SSD1306 OLED driver implemented over I2C without using any graphics libraries.

## Objective

To understand and implement the SSD1306 controller from the datasheet level, starting from raw I2C communication and building up to a full framebuffer-based driver.

---

## Hardware

- Arduino UNO Development Board
- SSD1306 128x64 OLED (I2C)

---

## Phase 1 – Low-Level Communication & Initialization

- Implemented direct I2C command transmission using Wire
- Verified display ON (0xAF) and OFF (0xAE)
- Developed custom `ssd1306_init()` based on datasheet command table
- Display initializes and operates without external libraries

---

## Upcoming Work

- Implement 1024-byte framebuffer
- Pixel mapping (x, y → page/bit)
- Page and column addressing
- Full buffer update routine
- Port to ESP32
- Port to STM32
