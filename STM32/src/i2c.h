#ifndef I2C_H
#define I2C_H
#include <stdint.h>

typedef struct{
    uint8_t SDA_PIN;
    uint8_t SCL_PIN;
    uint8_t delay_us;
} I2C_config;

#define RCC_APB2ENR (*(volatile uint32_t*)(0x40021000 + 0x18))
#define RCC_APB1ENR (*(volatile uint32_t*)(0x40021000 + 0x1C))
#define CRL_GPIOB (*(volatile uint32_t *)(0x40010C00 + 0x00))
#define ODR_GPIOB (*(volatile uint32_t *)(0x40010C00 + 0x0C))
#define CRH_GPIOC (*(volatile uint32_t*)(0x40011000 + 0x04))
#define ODR_GPIOC (*(volatile uint32_t *)(0x40011000 + 0x0C))

#define GPIOB_En (1<<3)

#define SDA_HIGH(cfg) (ODR_GPIOB |= (1<<(cfg)->SDA_PIN))
#define SDA_LOW(cfg) (ODR_GPIOB &= ~(1<<(cfg)->SDA_PIN))
#define SCL_HIGH(cfg) (ODR_GPIOB |= (1<<(cfg)->SCL_PIN))
#define SCL_LOW(cfg) (ODR_GPIOB &= ~(1<<(cfg)->SCL_PIN))
#define delay delay_alt(1)
#define ODR_BLINKON (ODR_GPIOC |= (1<<13))
#define ODR_BLINKOFF (ODR_GPIOC &= ~(1<<13))

void delay_alt(int us);

void i2c_gpio_config(I2C_config *cfg);
void i2c_start(I2C_config *cfg);
void i2c_write_byte(I2C_config *cfg, uint8_t cmd);
void i2c_stop(I2C_config *cfg);

void blink_setup(void);
void blink_test(void);

#endif