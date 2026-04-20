# SSD1306 Raw Driver

Bare-metal SSD1306 OLED driver implemented over I2C without using any graphics libraries.

## Objective

To understand and implement the SSD1306 controller from the datasheet level, starting from raw I2C communication and building up to a full framebuffer-based driver.

---

## Hardware
- STM32 BluePill (STM32F103C8T6)
- Arduino UNO Development Board
- SSD1306 128x64 OLED (I2C)

---

## Phase 1 – Low-Level Communication & Initialization

- Implemented direct I2C command transmission using Wire
- Verified display ON (0xAF) and OFF (0xAE)
- Developed custom `ssd1306_init()` based on datasheet command table
- Display initializes and operates without external libraries

## Phase 2 – Framebuffer & Pixel Rendering
- Implemented 1024-byte framebuffer (uint8_t ssd1306_buffer[1024])
- Pixel mapping via set_pixel(x, y) using page/bit math
- ssd1306_clear() to blank the framebuffer using memset
- ssd1306_update() pushes full 1024-byte buffer to display over I2C
- Handled Wire library 32-byte limit by chunking transmissions
- Successfully rendered single pixel at center of screen
## Phase 3 – Graphics Primitives
- Implemented drawLine() using Bresenham's line algorithm with vertical line special case
- Implemented drawRect() using four drawLine() calls
- Implemented drawCircle() using Midpoint Circle algorithm with 8-point symmetry
- Separated graphics functions into dedicated graphics.cpp file
## Phase 4 - Port to STM32 and BITBANG I2C
- Replaced STM32 hardware I2C (unreliable flag handling) with software bit-bang I2C using GPIO pins PB6 (SDA) and PB7 (SCL)
- Implemented I2C protocol manually: START, STOP, 8-bit data transmission, and 9th clock ACK pulse
- Calibrated software delays to achieve ~200–400 kHz communication speed
- Ported complete SSD1306 driver (framebuffer, graphics primitives) to STM32F103 without HAL or any external library
---

## Upcoming Work
- Code refactoring and modularization
- Character and string rendering (draw_char, draw_string)
