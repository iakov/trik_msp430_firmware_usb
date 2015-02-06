/*
 * trik_softi2c.h
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SOFTI2C_H_
#define TRIK_SOFTI2C_H_

//I2C registers
#define IICTL               0x00
#define IIDEV               0x01
#define IIREG               0x02
#define IIDAT               0x03
#define IIERR               0x04

//I2C errors
#define I2C_NO_ERROR        0x00

//Masks for bits of control register
#define I2C_ENABLE          0x80 //I2C enable
#define I2C_READ            0x20 //I2C read
#define I2C_WRITE           0x40 //I2C write

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
};

//I2C registers array
volatile struct tI2CRegisters I2C[MAX_I2CS];

//I2C ACK defines
#define NO_ACK              0x00
#define OK_ACK              0x01

//I2C ports and pins
#define I2C_DIR1            P2DIR
#define I2C_OUT1            P2OUT
#define I2C_IN1             P2IN
#define I2C_SEL1            P2SEL
#define SDA1                BIT0
#define SCL1                BIT3

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

void I2C_delay(uint16_t i2c_del);
//#define I2C_WAIT            I2C_delay(2000);

#endif /* TRIK_SOFTI2C_H_ */
