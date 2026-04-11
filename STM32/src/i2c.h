#ifndef I2C_H
#define I2C_H
#include <stdint.h>

void i2c_init(void);
void i2c_start(uint8_t A);
void i2c_write_byte(uint8_t cmd);
void i2c_stop(void);
#endif