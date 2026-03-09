#ifndef SSD1306_H
#define SSD1306_H
#include <Arduino.h>
extern uint8_t ssd1306_buffer[1024];

void ssd1306_init();
void ssd1306_write_command(uint8_t cmd);
void ssd1306_clear();
void set_pixel(uint8_t x, uint8_t y);
void ssd1306_update();

#endif
