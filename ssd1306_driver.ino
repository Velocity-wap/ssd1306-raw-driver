#include <Wire.h>
#include "ssd1306.h"
#include <string.h>

void setup(){
    Wire.begin();
    ssd1306_init();
    ssd1306_clear();
    ssd1306_update();
}

void loop(){
  // drawLine(0,0,0,20);         //vertical
  // ssd1306_update();
  drawLine(0, 0, 127, 63);   //diagonal
  ssd1306_update();
  // drawLine(0, 0, 127, 10);   //gentle slope
  // ssd1306_update();
  // drawLine(0, 0, 25, 63);    //steep slope
  // ssd1306_update();
  // drawLine(127, 0, 0, 63);   //going left
  // ssd1306_update();
  drawCircle(64, 32, 20);   //draws circle
  ssd1306_update();
  drawRect(10, 10, 50, 30); //draws rectangle
  ssd1306_update();
  delay(1000);
}