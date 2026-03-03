#include <Wire.h>
#include "ssd1306.h"

void setup(){
  Wire.begin();
  ssd1306_init();
}

void loop(){
  ssd1306_write_command(0xAF);
  delay(1000);
  ssd1306_write_command(0xAE);
  delay(1000);
}