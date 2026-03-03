#include "ssd1306.h"
#include <Wire.h>

void ssd1306_write_command(uint8_t cmd){
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);
  Wire.write(cmd);
  Wire.endTransmission();
}

void ssd1306_init(){
  ssd1306_write_command(0xA8);//Set Mux ratio 
  ssd1306_write_command(0x3F);//64 rows
  ssd1306_write_command(0xD3);//set display offset
  ssd1306_write_command(0x00);//no offset
  ssd1306_write_command(0x40);//set display start line = 0
  ssd1306_write_command(0xA1);//segment remap(horizontal flip)
  ssd1306_write_command(0xC8);//COM scan direction (vertical flip)
  ssd1306_write_command(0xDA);//set COM pins config
  ssd1306_write_command(0x12);//alterantive config for 128x64
  ssd1306_write_command(0x81);//set contrast
  ssd1306_write_command(0x7F);//medium brightness
  ssd1306_write_command(0xA4);//display follows RAM content
  ssd1306_write_command(0xA6);//nromal display (white pixels on black background)...there is another which shows black pixels on white background(A7h)
  ssd1306_write_command(0xD5);//set oscillator frequency
  ssd1306_write_command(0x80);//default frequency
  ssd1306_write_command(0x14);//enable charge pump. Display needs ~7.5v to light up the pixels but the arduino gives only 3.3 or 5v so charge pump is a tiny circuit inside the chip which boosts the voltage to what the display needs.
  ssd1306_write_command(0xAF);//display on
}