#include "i2c.h"
#include "ssd1306.h"

int main(void) {
    blink_setup();      // LED for debugging
    i2c_init();         // Initialize I2C
    
    ssd1306_init();     // Initialize display
    ssd1306_clear();    // Clear buffer
    
    // Draw something
    drawLine(10, 10, 118, 54);
    drawRect(20, 20, 30, 30);
    drawCircle(64, 32, 20);
    
    ssd1306_update();   // Send buffer to display (displays' RAM basically)
    
    while(1) {
        // Keep display on
    }
}