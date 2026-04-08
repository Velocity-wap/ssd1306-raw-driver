#include <stdint.h>

void delay_alt(int us){
    
    for(volatile int i=0; i<(us * 8); i++);//delay loop to use instead of poll

}

uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18);//to configure GPIOB 
uint32_t *APB1ENR = (uint32_t *)(0x40021000 + 0x1C);
uint32_t *CR2 = (uint32_t *)(0x40005400 + 0x04);//Enable peripheral clock frequency
uint32_t *CCR = (uint32_t *)(0x40005400 + 0x1C);//enable i2c bus frequency
uint32_t *TRISE = (uint32_t *)(0x40005400 + 0x20);//Rise time configuration
uint32_t *CR1 = (uint32_t *)(0x40005400 + 0x00);//enable i2c periphal and start n' end bit
uint32_t *SR1 = (uint32_t *)(0x40005400 + 0x14);//Status register 1
uint32_t *SR2 = (uint32_t *)(0x40005400 + 0x18);//Status register 2
uint32_t *DR = (uint32_t *)(0x40005400 + 0x10);//Data register

void i2c_init(void){

    *APB2ENR |= (1<<3);
    *APB1ENR |= (1<<21);
    *CR2 &= ~(0x3f<<0);
    *CR2 |= (1<<3);// Set at 8MHz
    *CCR &= ~(0xfff << 0);
    *CCR |= (40<<0);//setting the i2c communication freq at 100kHz
    *TRISE &= ~(0x3f<<0);
    *TRISE |= (0x9<<0); //for standard, max rise time is 1000ns so 9 is trise value
    *CR1 |= (1<<0); //enable peripheral bit
    for (int i=0; i<1000; i++);//For PE to stabilize

}
void i2c_start(void){

    *CR1 |=(1<<8);//Start condition
    while(!(*SR1 & (1<<0)));//while the 0th bit is zero then while(0)
    *DR = (0x3C << 1);// Address bit, Shifting 0x3C left makes room for the 0 (Write) bit
    delay_alt(100); // delay instead of ADDR poll
	(void)(*SR1);
    (void)(*SR2);


}
void i2c_write_byte(uint8_t cmd){

    *DR = cmd;
    delay_alt(100);
}
void i2c_stop(void){

    *CR1 |= (1<<9);
    delay_alt(100);

}
