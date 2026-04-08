#ifndef SSD1306_H
#define SSD1306_H
#include <Arduino.h>

void ssd1306_init();
void ssd1306_write_command(uint8_t cmd);
extern uint8_t ssd1306_buffer[1024];
void ssd1306_clear();
void set_pixel(uint8_t x, uint8_t y);
void ssd1306_update();
void drawLine(int xa, int ya, int xb, int yb);
void drawRect(int x, int y, int w, int h);
void drawCircle(int x1, int y1, int r);
void plotPoints(int xctr, int yctr, int x, int y);
#endif