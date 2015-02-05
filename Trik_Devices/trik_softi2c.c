/*
 * trik_softi2c.c
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_softi2c.h"
#include "trik_devices.h"

void I2C_delay(uint16_t i2c_del)
{
    do
    {
        _nop();
    }
    while(--i2c_del);
}

void I2C_lowSDA(uint8_t I2C_NUMBER)
{
    switch (I2C_NUMBER)
    {
        case I2C1:
            I2C_DIR1 |= SDA1;
            I2C_WAIT
            break;
        default:;
        break;
    }
}

void I2C_highSDA(uint8_t I2C_NUMBER)
{
    switch (I2C_NUMBER)
    {
        case I2C1:
            I2C_DIR1 &= ~SDA1;
            I2C_WAIT
            break;
        default:;
        break;
    }
}

void I2C_lowSCL(uint8_t I2C_NUMBER)
{
    switch (I2C_NUMBER)
    {
        case I2C1:
            I2C_OUT1 &= ~SCL1;
            I2C_WAIT
            break;
        default:;
        break;
    }
}

void I2C_highSCL(uint8_t I2C_NUMBER)
{
    switch (I2C_NUMBER)
    {
        case I2C1:
            I2C_OUT1 |= SCL1;
            I2C_WAIT
            break;
        default:;
        break;
    }
}

void I2C_init(uint8_t I2C_NUMBER)
{
    if (!(isSlotBusy(I2C_NUMBER)))
    {
        reseveSlot(I2C_NUMBER);
        switch (I2C_NUMBER)
        {
            case I2C1:
                I2C_SEL1 &= ~SDA1;
                I2C_SEL1 &= ~SCL1;
                I2C_OUT1 &= ~SCL1;
                I2C_OUT1 &= ~SDA1;
                I2C_DIR1 |= SCL1;
                I2C_DIR1 &= ~SDA1;
                I2C_highSCL(I2C_NUMBER);
                I2C_lowSDA(I2C_NUMBER);
                I2C_highSDA(I2C_NUMBER);
                break;
            default:;
            break;
        }
    }

}
