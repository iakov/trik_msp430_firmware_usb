/*
 * trik_hmc5883l.c
 *
 *  Created on: Fabruary 6, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_hmc5883l.h"
#include "trik_softi2c.h"
#include "trik_devices.h"

void HMC5883L_init(uint8_t I2C_NUMBER)
{
    I2C_writechar(I2C_NUMBER, 0x3C, 0x02, 0x00);
}

uint16_t HMC5883L_readX(uint8_t I2C_NUMBER)
{
    uint16_t gh, gl;
    gh = I2C_readchar(I2C_NUMBER, 0x3C, 0x03);
    gl = I2C_readchar(I2C_NUMBER, 0x3C, 0x04) + (gh << 8);
    return gl;
}

uint16_t HMC5883L_readY(uint8_t I2C_NUMBER)
{
    uint16_t gh, gl;
    gh = I2C_readchar(I2C_NUMBER, 0x3C, 0x07);
    gl = I2C_readchar(I2C_NUMBER, 0x3C, 0x08) + (gh << 8);
    return gl;
}

uint16_t HMC5883L_readZ(uint8_t I2C_NUMBER)
{
    uint16_t gh, gl;
    gh = I2C_readchar(I2C_NUMBER, 0x3C, 0x05);
    gl = I2C_readchar(I2C_NUMBER, 0x3C, 0x06) + (gh << 8);
    return gl;
}
