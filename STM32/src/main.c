#include "i2c.h"
#include "ssd1306.h"

I2C_config i2c = {
    .SDA_PIN = 6,
    .SCL_PIN = 7,
    .delay_us = 1,
};

int main(void) {
    blink_setup();      // LED setup for debugging
    i2c_gpio_config();      // Configure PB6, PB7 as outputs
    
    ssd1306_init();     // Initialize display
    ssd1306_clear();    // Clear framebuffer
    
    // Draw something
    set_pixel(64, 32);
    drawLine(10, 10, 118, 54);
    drawRect(20, 20, 40, 30);
    drawCircle(64, 32, 20);
    
    ssd1306_update();   // Send framebuffer to display
    
    // Success indicator
    for(int i = 0; i < 10; i++) blink_test();
    
    while(1);           // Stop here
}