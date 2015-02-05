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

void I2C_start(uint8_t I2C_NUMBER)
{
    switch (I2C_NUMBER)
    {
        case I2C1:
            I2C_highSCL(I2C_NUMBER);
            I2C_highSDA(I2C_NUMBER);
            I2C_highSCL(I2C_NUMBER);
            I2C_lowSDA(I2C_NUMBER);
            I2C_lowSCL(I2C_NUMBER);
            I2C_highSDA(I2C_NUMBER);
            break;
        default:;
        break;
    }
}

void I2C_stop(uint8_t I2C_NUMBER)
{
    switch (I2C_NUMBER)
    {
        case I2C1:
            I2C_lowSCL(I2C_NUMBER);
            I2C_lowSDA(I2C_NUMBER);
            I2C_highSCL(I2C_NUMBER);
            I2C_lowSDA(I2C_NUMBER);
            I2C_highSCL(I2C_NUMBER);
            I2C_highSDA(I2C_NUMBER);
            break;
        default:;
        break;
    }
}

uint8_t I2C_read(uint8_t I2C_NUMBER, uint8_t i2c_ack)
{
    uint8_t i, c = 0x00;
    switch (I2C_NUMBER)
    {
        case I2C1:
            for (i=0; i<8; i++)
            {
                c = c << 1;
                I2C_highSCL(I2C_NUMBER);
                if (I2C_IN1 & SDA1) c++;
                I2C_lowSCL(I2C_NUMBER);
            }
            if (i2c_ack) I2C_lowSDA(I2C_NUMBER);
            I2C_highSCL(I2C_NUMBER);
            I2C_lowSCL(I2C_NUMBER);
            return c;
        default:;
        return NO_ACK;
    }
}

uint8_t I2C_write(uint8_t I2C_NUMBER, uint8_t i2c_dta)
{
    uint8_t i, ack;
    switch (I2C_NUMBER)
    {
        case I2C1:
            for (i=0; i<8; i++)
            {
                I2C_lowSCL(I2C_NUMBER);
                if (i2c_dta & 0x80)
                    I2C_highSDA(I2C_NUMBER);
                else
                    I2C_lowSDA(I2C_NUMBER);
                I2C_highSCL(I2C_NUMBER);
                i2c_dta <<= 1;
            }
            I2C_lowSCL(I2C_NUMBER);
            I2C_highSDA(I2C_NUMBER);
            I2C_highSCL(I2C_NUMBER);
            if (I2C_IN1 & SDA1)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            I2C_lowSCL(I2C_NUMBER);
            return ack;
        default:;
        return NO_ACK;
    }
}
