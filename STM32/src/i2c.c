#include <stdint.h>
#include "i2c.h"

void delay_alt(int us){
    
    for(volatile int i=0; i<(us * 8); i++);//delay loop to use instead of poll

}
uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18); //to configure GPIOB 
uint32_t *APB1ENR = (uint32_t *)(0x40021000 + 0x1C);
uint32_t *ODR_IOC = (uint32_t *)(0x40011000 + 0x0C);//GPIOC
uint32_t *CRH_led = (uint32_t *)(0x40011000 + 0x04);
uint32_t *ODR_IOB = (uint32_t *)(0x40010C00 + 0x0C);//GPIOB
uint32_t *CRL_IOB = (uint32_t *)(0x40010C00 + 0x00);
// //i2c setup-----------
// uint32_t *CRL = (uint32_t *)(0x40010C00  + 0x00); //PB7 and PB6 (GPIOB)
// uint32_t *CR2 = (uint32_t *)(0x40005400 + 0x04); //Enable peripheral clock frequency
// uint32_t *CCR = (uint32_t *)(0x40005400 + 0x1C); //enable i2c bus frequency
// uint32_t *TRISE = (uint32_t *)(0x40005400 + 0x20); //Rise time configuration
// uint32_t *CR1 = (uint32_t *)(0x40005400 + 0x00); //enable i2c periphal and start n' end bit
// uint32_t *SR1 = (uint32_t *)(0x40005400 + 0x14); //Status register 1
// uint32_t *SR2 = (uint32_t *)(0x40005400 + 0x18); //Status register 2
// uint32_t *DR = (uint32_t *)(0x40005400 + 0x10); //Data register
//--------------------------

void blink_setup(void){

	*APB2ENR |= (1<<4);
	*CRH_led &= ~(0xf << 20);
	*CRH_led |= (1<<20);
}

void blink_test(void){
    *ODR_IOC |= (1<<13);
    for(int i=0; i<100000; i++);
    *ODR_IOC &= ~(1<<13);
    for(int i=0; i<100000; i++);
}

void i2c_gpio_config(void) {
    *APB2ENR |= (1<<3);
    *CRL_IOB &= ~((0xF<<24) | (0xF<<28));
    *CRL_IOB |= ((0x3<<24) | (0x3<<28));  // 50MHz
}

void i2c_start(void){
    *ODR_IOB |=(1<<6)|(1<<7);//SDA and SCL toggle on
    delay_alt(1);
    *ODR_IOB &= ~(1<<6);//STARTS
    delay_alt(1);
    *ODR_IOB &= ~(1<<7);
}

void i2c_stop(void){
    *ODR_IOB |= (1<<7); //SCL high
    delay_alt(1);
    *ODR_IOB |= (1<<6); //SDA high
    delay_alt(1);
}

void i2c_write_byte(uint8_t cmd){
    for(int i=0; i<8; i++){

        if((cmd & 0x80) != 0){ 
            *ODR_IOB |= (1<<6);//SDA high
        }
        else{
            *ODR_IOB &=~(1<<6);//SDA low
        }
        delay_alt(1);
        
        *ODR_IOB |= (1<<7);//SCL HIGH, now reads slave data
        delay_alt(1);
        
        *ODR_IOB &=~(1<<7);
        delay_alt(1);
        
        cmd <<= 1; //SHIFT
    }
    delay_alt(1);
    //Final 9th ACK bit
    *ODR_IOB |= (1<<6);
    delay_alt(1);
    *ODR_IOB |= (1<<7);
    delay_alt(1);
    *ODR_IOB &=~(1<<7);
}
// void i2c_init(void){
    
//     // *APB2ENR |= (1<<3);
//     // *APB1ENR |= (1<<21);
// 	// *CRL &= ~((0xf<<24) | (0xf<<28));
// 	// *CRL |= (0xd<<24) | (0xd<<28); //1011 max 50MHz and AFO/P
//     // *CR2 &= ~(0x3f<<0);
//     // *CR2 |= (1<<3); //Set at 8MHz
//     // *CCR &= ~(0xfff << 0);
//     // *CCR |= (40<<0); //setting the i2c communication freq at 100kHz
//     // *TRISE &= ~(0x3f<<0);
//     // *TRISE |= (0x9<<0); //for standard, max rise time is 1000ns so 9 is trise value
//     // *CR1 |= (1<<0); //enable peripheral bit
//     // for (int i=0; i<1000; i++); //For PE to stabilize
// }

// void i2c_start(uint8_t A){

//     *CR1 |=(1<<8); //Start condition
//     while(!(*SR1 & (1<<0))); //while the 0th bit is zero then while(0)
//     *DR = (A << 1); // Address bit, Shifting 0x3C left makes room for the 0 (Write) bit
//     while(!(*SR1 & (1<<1))); //Check ADDR poll
// 	(void)(*SR1);
//     (void)(*SR2);
//     //TxE = 1 happens automatically
// }

// void i2c_write_byte(uint8_t data, uint8_t is_last) {
//     while(!(*SR1 & (1<<7)));  // Check TxE poll
//     *DR = data;
//     if(is_last) {
//         // Last byte: wait for BTF or use delay
//         delay_alt(100);
//     }
// }

// void i2c_stop(void){
        
//     delay_alt(100);    
//     *CR1 |= (1<<9); //STOP
//     delay_alt(100);
// }