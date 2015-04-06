/*
 * trik_softi2c.h
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SOFTI2C_H_
#define TRIK_SOFTI2C_H_

//I2C errors
#define I2C_NO_ERROR        0x00
#define I2C_DEV_ERR         0xFF

//Masks for bits of control register
#define I2C_ENABLE          0x80 // I2C enable
#define I2C_READ            0x20 // I2C read
#define I2C_WRITE           0x40 // I2C write
#define I2C_SENS            0x10 // I2C read sensor
#define I2C_PULL            0x08 // I2C pullup resistors

//Max I2Cs
#define MAX_I2CS            0x04

//I2C delay
uint16_t Idelay;

//I2C registers
struct tI2CRegisters
{
    uint8_t ICTL;
    uint8_t IDEV;
    uint8_t IREG;
    uint8_t IDAT;
    uint8_t IERR;
    uint8_t ISTA;
    uint16_t IIDX;
    uint16_t IVAL;
};

//Registers
#define IICTL               0x00
#define IIDEV               0x01
#define IIREG               0x02
#define IIDAT               0x03
#define IIERR               0x04
#define IIIDX               0x05
#define IIVAL               0x06
#define IIDEL               0x07
#define IIVER               0x08

//I2C registers array
volatile struct tI2CRegisters I2C[MAX_I2CS];

//I2C ACK defines
#define NO_ACK              0x00
#define OK_ACK              0x01

//I2C ports and pins

#define I2C_DIR1            P6DIR
#define I2C_OUT1            P6OUT
#define I2C_IN1             P6IN
#define I2C_SEL1            P6SEL
#define I2C_PUL1            P6REN
#define SCL1                BIT0    // JA6
#define SDA1                BIT1    // JA5

#define I2C_DIR2            P6DIR
#define I2C_OUT2            P6OUT
#define I2C_IN2             P6IN
#define I2C_SEL2            P6SEL
#define I2C_PUL2            P6REN
#define SCL2                BIT2    // JA4
#define SDA2                BIT3    // JA3

#define I2C_DIR3            P6DIR
#define I2C_OUT3            P6OUT
#define I2C_IN3             P6IN
#define I2C_SEL3            P6SEL
#define I2C_PUL3            P6REN
#define SCL3                BIT4    // JA2
#define SDA3                BIT5    // JA1

#define I2C_DIR4            P2DIR
#define I2C_OUT4            P2OUT
#define I2C_IN4             P2IN
#define I2C_SEL4            P2SEL
#define I2C_PUL4            P2REN
#define SCL4                BIT3    // JB1B
#define SDA4                BIT0    // JB1A

#define I2C_DIR5_1          P1DIR
#define I2C_OUT5_1          P1OUT
#define I2C_IN5_1           P1IN
#define I2C_SEL5_1          P1SEL
#define I2C_PUL5_1          P1REN
#define I2C_DIR5_2          P2DIR
#define I2C_OUT5_2          P2OUT
#define I2C_IN5_2           P2IN
#define I2C_SEL5_2          P2SEL
#define I2C_PUL5_2          P2REN
#define SCL5                BIT0    // JB2B
#define SDA5                BIT4    // JB2A

#define I2C_DIR6            P2DIR
#define I2C_OUT6            P2OUT
#define I2C_IN6             P2IN
#define I2C_SEL6            P2SEL
#define I2C_PUL6            P2REN
#define SCL6                BIT2    // JB3B
#define SDA6                BIT5    // JB3A

#define I2C_DIR7_1          P1DIR
#define I2C_OUT7_1          P1OUT
#define I2C_IN7_1           P1IN
#define I2C_SEL7_1          P1SEL
#define I2C_PUL7_1          P1REN
#define I2C_DIR7_2          P2DIR
#define I2C_OUT7_2          P2OUT
#define I2C_IN7_2           P2IN
#define I2C_SEL7_2          P2SEL
#define I2C_PUL7_2          P2REN
#define SCL7                BIT6    // JB4B
#define SDA7                BIT1    // JB4A

//Sensor defines
#define NXTTEMP             0x0000
#define HMC5883L_X          0x0001
#define HMC5883L_Y          0x0002
#define HMC5883L_Z          0x0003
#define MCP3424_CH1			0x0004
#define MCP3424_CH2			0x0005
#define MCP3424_CH3			0x0006
#define MCP3424_CH4			0x0007

void I2C_lowSDA(uint8_t I2C_NUMBER);
void I2C_highSDA(uint8_t I2C_NUMBER);
void I2C_lowSCL(uint8_t I2C_NUMBER);
void I2C_highSCL(uint8_t I2C_NUMBER);
void I2C_init(uint8_t I2C_NUMBER);
void I2C_start(uint8_t I2C_NUMBER);
void I2C_stop(uint8_t I2C_NUMBER);
uint8_t I2C_read(uint8_t I2C_NUMBER, uint8_t i2c_ack);
uint8_t I2C_write(uint8_t I2C_NUMBER, uint8_t i2c_dta);
uint8_t I2C_readchar(uint8_t I2C_NUMBER, uint8_t i2c_dev, uint8_t i2c_reg);
void I2C_writechar(uint8_t I2C_NUMBER, uint8_t i2c_dev, uint8_t i2c_reg, uint8_t i2c_val);
void I2C_disable(uint8_t I2C_NUMBER);
void I2C_readsensor(uint8_t I2C_NUMBER);
void I2C_handler(uint8_t I2C_NUMBER);

void I2C_delay(uint16_t i2c_del);
//#define I2C_WAIT            I2C_delay(2000);

#endif /* TRIK_SOFTI2C_H_ */
