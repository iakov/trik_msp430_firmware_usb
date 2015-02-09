/*
 * trik_nxttemp.c
 *
 *  Created on: Fabruary 6, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_hmc5883l.h"
#include "trik_softi2c.h"
#include "trik_devices.h"

uint16_t NXTTEMP_readTemperature(uint8_t I2C_NUMBER)
{
    uint16_t tl;
    tl = I2C_readchar(I2C_NUMBER, 0x98, 0x00);
    return tl;
}
