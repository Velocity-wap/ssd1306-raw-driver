#include <stdint.h>
#include "i2c.h"

void delay_alt(int us){
    
    for(volatile int i=0; i<(us * 8); i++);//delay loop to use instead of poll

}

void blink_setup(void){

	RCC_APB2ENR |= (1<<4);
	CRH_GPIOC &= ~(0xf << 20);
	CRH_GPIOC |= (1<<20);
}

void blink_test(void){
    ODR_BLINKON;
    for(int i=0; i<100000; i++);
    ODR_BLINKOFF;
    for(int i=0; i<100000; i++);
}

void i2c_gpio_config(I2C_config *cfg){
    RCC_APB2ENR |= GPIOB_En;
    CRL_GPIOB &= ~((0xF<<(cfg->SDA_PIN*4))|(0xF<<(cfg->SCL_PIN*4)));
    CRL_GPIOB |= ((0x3<<(cfg->SDA_PIN*4))|(0x3<<(cfg->SCL_PIN*4)));  // 50MHz
}

void i2c_start(I2C_config *cfg){
    SDA_HIGH(cfg); SCL_HIGH(cfg);//SDA and SCL toggle on
    delay;
    SDA_LOW(cfg);//STARTS
    delay;
    SCL_LOW(cfg);
}

void i2c_stop(I2C_config *cfg){
    SDA_LOW(cfg);
    delay;
    SCL_HIGH(cfg); //SCL high
    delay;
    SDA_HIGH(cfg); //SDA high
    delay;
}

void i2c_write_byte(I2C_config *cfg, uint8_t cmd){
    for(int i=0; i<8; i++){

        if((cmd & 0x80) != 0){ 
            SDA_HIGH(cfg);//SDA high
        }
        else{
            SDA_LOW(cfg);//SDA low
        }
        delay;
        
        SCL_HIGH(cfg);//SCL HIGH, now reads slave data
        delay;
        
        SCL_LOW(cfg);
        delay;
        
        cmd <<= 1; //SHIFT
    }
    delay;
    //Final 9th ACK bit
    SDA_HIGH(cfg);
    delay;
    SCL_HIGH(cfg);
    delay;
    SCL_LOW(cfg);
}