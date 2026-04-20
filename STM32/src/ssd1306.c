#include "ssd1306.h"
#include "i2c.h"
#include <string.h>
uint8_t ssd1306_buffer[1024];
void ssd1306_write_command(uint8_t cmd){
    i2c_start();
    i2c_write_byte(0x78);
    i2c_write_byte(0x00);   
    i2c_write_byte(cmd);  
    i2c_stop();
}

void ssd1306_init(void){
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
  ssd1306_write_command(0x8D); // charge pump command
  ssd1306_write_command(0x14);//enable charge pump. Display needs ~7.5v to light up the pixels but the arduino gives only 3.3 or 5v so charge pump is a tiny circuit inside the chip which boosts the voltage to what the display needs.
  ssd1306_write_command(0xAF);//display on
}

void ssd1306_clear(void){
  memset(ssd1306_buffer, 0x00,sizeof(ssd1306_buffer) );
}
void set_pixel(uint8_t x, uint8_t y){
  uint8_t page = y/8; //each page has 8 rows so vertical position would be divided by 8 to get the page it is at.
  uint16_t index = (page * 128) + x;  //  which exact byte in the buffer array (0-1023)
  uint8_t bit = y % 8;  // which pixel vertically inside that byte (0-7)
  ssd1306_buffer[index] |= (1 << bit);  // Buffer is just a flat array that respresents all 8 pages.
}
void ssd1306_update(void){
  ssd1306_write_command(0xAE); //TURN off the display until update is done
  ssd1306_write_command(0x20); //setting up addressing modes
  ssd1306_write_command(0x00); //setting up horizontal addressing mode

  ssd1306_write_command(0x21); //set column address
  ssd1306_write_command(0x00); //initially from 0
  ssd1306_write_command(0x7f); //ends at 127

  ssd1306_write_command(0x22); //set page address
  ssd1306_write_command(0x00); //initially from 0
  ssd1306_write_command(0x07); //ends at 7 
    
    i2c_start();
    i2c_write_byte(0x78);   // Address
    i2c_write_byte(0x40);   // Control byte (data)
    
    for(int i = 0; i < 1024; i++) {
        i2c_write_byte(ssd1306_buffer[i]);
    }
    
    i2c_stop();
    ssd1306_write_command(0xAF);//finally turn it on once everything is done
}

void *memset(void *s, int c, unsigned int n) {
    unsigned char *p = s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}