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


#endif /* TRIK_SOFTI2C_H_ */
