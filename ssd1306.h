#ifndef SSD1306_H
#define SSD1306_H
#include <Arduino.h>

void ssd1306_init();
void ssd1306_write_command(uint8_t cmd);

#endif