#ifndef I2C_H
#define I2C_H
#include <stdint.h>

void delay_alt(int us);
void i2c_gpio_config(void);
void i2c_start(void);
void i2c_write_byte(uint8_t cmd);
void i2c_stop(void);
void blink_setup(void);
void blink_test(void);
#endif