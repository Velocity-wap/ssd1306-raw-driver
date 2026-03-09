#include <Wire.h>
#include "ssd1306.h"
#include <string.h>
int x = 62;

void setup(){
    Wire.begin();
    ssd1306_init();
    ssd1306_clear();
    ssd1306_update();
}

void loop(){
  ssd1306_clear();
  set_pixel(x, 31);
  set_pixel(x, 32);
  set_pixel(x, 33);
  ssd1306_update();
  x += 1;
  if (x > 67){
    x = 62;
  }
  delay(1000);
}