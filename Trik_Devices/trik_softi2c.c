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
            I2C_delay(Idelay);
            break;
        case I2C2:
            I2C_DIR2 |= SDA2;
            I2C_delay(Idelay);
            break;
        case I2C3:
            I2C_DIR3 |= SDA3;
            I2C_delay(Idelay);
            break;
        case I2C4:
            I2C_DIR4 |= SDA4;
            I2C_delay(Idelay);
            break;
        case I2C5:
            I2C_DIR5_2 |= SDA5;
            I2C_delay(Idelay);
            break;
        case I2C6:
            I2C_DIR6 |= SDA6;
            I2C_delay(Idelay);
            break;
        case I2C7:
            I2C_DIR7_2 |= SDA7;
            I2C_delay(Idelay);
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
            I2C_delay(Idelay);
            break;
        case I2C2:
            I2C_DIR2 &= ~SDA2;
            I2C_delay(Idelay);
            break;
        case I2C3:
            I2C_DIR3 &= ~SDA3;
            I2C_delay(Idelay);
            break;
        case I2C4:
            I2C_DIR4 &= ~SDA4;
            I2C_delay(Idelay);
            break;
        case I2C5:
            I2C_DIR5_2 &= ~SDA5;
            I2C_delay(Idelay);
            break;
        case I2C6:
            I2C_DIR6 &= ~SDA6;
            I2C_delay(Idelay);
            break;
        case I2C7:
            I2C_DIR7_2 &= ~SDA7;
            I2C_delay(Idelay);
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
            I2C_delay(Idelay);
            break;
        case I2C2:
            I2C_OUT2 &= ~SCL2;
            I2C_delay(Idelay);
            break;
        case I2C3:
            I2C_OUT3 &= ~SCL3;
            I2C_delay(Idelay);
            break;
        case I2C4:
            I2C_OUT4 &= ~SCL4;
            I2C_delay(Idelay);
            break;
        case I2C5:
            I2C_OUT5_1 &= ~SCL5;
            I2C_delay(Idelay);
            break;
        case I2C6:
            I2C_OUT6 &= ~SCL6;
            I2C_delay(Idelay);
            break;
        case I2C7:
            I2C_OUT7_1 &= ~SCL7;
            I2C_delay(Idelay);
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
            I2C_delay(Idelay);
            break;
        case I2C2:
            I2C_OUT2 |= SCL2;
            I2C_delay(Idelay);
            break;
        case I2C3:
            I2C_OUT3 |= SCL3;
            I2C_delay(Idelay);
            break;
        case I2C4:
            I2C_OUT4 |= SCL4;
            I2C_delay(Idelay);
            break;
        case I2C5:
            I2C_OUT5_1 |= SCL5;
            I2C_delay(Idelay);
            break;
        case I2C6:
            I2C_OUT6 |= SCL6;
            I2C_delay(Idelay);
            break;
        case I2C7:
            I2C_OUT7_1 |= SCL7;
            I2C_delay(Idelay);
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
            case I2C2:
                I2C_SEL2 &= ~SDA2;
                I2C_SEL2 &= ~SCL2;
                I2C_OUT2 &= ~SCL2;
                I2C_OUT2 &= ~SDA2;
                I2C_DIR2 |= SCL2;
                I2C_DIR2 &= ~SDA2;
                I2C_highSCL(I2C_NUMBER);
                I2C_lowSDA(I2C_NUMBER);
                I2C_highSDA(I2C_NUMBER);
                break;
            case I2C3:
                I2C_SEL3 &= ~SDA3;
                I2C_SEL3 &= ~SCL3;
                I2C_OUT3 &= ~SCL3;
                I2C_OUT3 &= ~SDA3;
                I2C_DIR3 |= SCL3;
                I2C_DIR3 &= ~SDA3;
                I2C_highSCL(I2C_NUMBER);
                I2C_lowSDA(I2C_NUMBER);
                I2C_highSDA(I2C_NUMBER);
                break;
            case I2C4:
                I2C_SEL4 &= ~SDA4;
                I2C_SEL4 &= ~SCL4;
                I2C_OUT4 &= ~SCL4;
                I2C_OUT4 &= ~SDA4;
                I2C_DIR4 |= SCL4;
                I2C_DIR4 &= ~SDA4;
                I2C_highSCL(I2C_NUMBER);
                I2C_lowSDA(I2C_NUMBER);
                I2C_highSDA(I2C_NUMBER);
                break;
            case I2C5:
                I2C_SEL5_2 &= ~SDA5;
                I2C_SEL5_1 &= ~SCL5;
                I2C_OUT5_1 &= ~SCL5;
                I2C_OUT5_2 &= ~SDA5;
                I2C_DIR5_1 |= SCL5;
                I2C_DIR5_2 &= ~SDA5;
                I2C_highSCL(I2C_NUMBER);
                I2C_lowSDA(I2C_NUMBER);
                I2C_highSDA(I2C_NUMBER);
                break;
            case I2C6:
                I2C_SEL6 &= ~SDA6;
                I2C_SEL6 &= ~SCL6;
                I2C_OUT6 &= ~SCL6;
                I2C_OUT6 &= ~SDA6;
                I2C_DIR6 |= SCL6;
                I2C_DIR6 &= ~SDA6;
                I2C_highSCL(I2C_NUMBER);
                I2C_lowSDA(I2C_NUMBER);
                I2C_highSDA(I2C_NUMBER);
                break;
            case I2C7:
                I2C_SEL7_2 &= ~SDA7;
                I2C_SEL7_1 &= ~SCL7;
                I2C_OUT7_1 &= ~SCL7;
                I2C_OUT7_2 &= ~SDA7;
                I2C_DIR7_1 |= SCL7;
                I2C_DIR7_2 &= ~SDA7;
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
    I2C_highSCL(I2C_NUMBER);
    I2C_highSDA(I2C_NUMBER);
    I2C_highSCL(I2C_NUMBER);
    I2C_lowSDA(I2C_NUMBER);
    I2C_lowSCL(I2C_NUMBER);
    I2C_highSDA(I2C_NUMBER);
}

void I2C_stop(uint8_t I2C_NUMBER)
{
    I2C_lowSCL(I2C_NUMBER);
    I2C_lowSDA(I2C_NUMBER);
    I2C_highSCL(I2C_NUMBER);
    I2C_lowSDA(I2C_NUMBER);
    I2C_highSCL(I2C_NUMBER);
    I2C_highSDA(I2C_NUMBER);
}

uint8_t I2C_read(uint8_t I2C_NUMBER, uint8_t i2c_ack)
{
    uint8_t i, c = 0x00;
    for (i=0; i<8; i++)
    {
        c = c << 1;
        I2C_highSCL(I2C_NUMBER);
        if (I2C_NUMBER == I2C1)
            if (I2C_IN1 & SDA1) c++;
        if (I2C_NUMBER == I2C2)
            if (I2C_IN2 & SDA2) c++;
        if (I2C_NUMBER == I2C3)
            if (I2C_IN3 & SDA3) c++;
        if (I2C_NUMBER == I2C4)
            if (I2C_IN4 & SDA4) c++;
        if (I2C_NUMBER == I2C5)
            if (I2C_IN5_2 & SDA5) c++;
        if (I2C_NUMBER == I2C6)
            if (I2C_IN6 & SDA6) c++;
        if (I2C_NUMBER == I2C7)
            if (I2C_IN7_2 & SDA7) c++;
        I2C_lowSCL(I2C_NUMBER);
    }
    if (i2c_ack) I2C_lowSDA(I2C_NUMBER);
    I2C_highSCL(I2C_NUMBER);
    I2C_lowSCL(I2C_NUMBER);
    if ((I2C_NUMBER>=I2C1) && (I2C_NUMBER<=I2C7))
        return c;
    else
        return I2C_DEV_ERR;
}

uint8_t I2C_write(uint8_t I2C_NUMBER, uint8_t i2c_dta)
{
    uint8_t i, ack;
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
    switch (I2C_NUMBER)
    {
        case I2C1:
            if (I2C_IN1 & SDA1)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            break;
        case I2C2:
            if (I2C_IN2 & SDA2)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            break;
        case I2C3:
            if (I2C_IN3 & SDA3)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            break;
        case I2C4:
            if (I2C_IN4 & SDA4)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            break;
        case I2C5:
            if (I2C_IN5_2 & SDA5)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            break;
        case I2C6:
            if (I2C_IN6 & SDA6)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            break;
        case I2C7:
            if (I2C_IN7_2 & SDA7)
                ack = NO_ACK;
            else
                ack = OK_ACK;
            break;
        default:;
            ack = I2C_DEV_ERR;
            break;
    }
    I2C_lowSCL(I2C_NUMBER);
    return ack;
}

uint8_t I2C_readchar(uint8_t I2C_NUMBER, uint8_t i2c_dev, uint8_t i2c_reg)
{
    uint8_t res;
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, i2c_dev);
    I2C_write(I2C_NUMBER, i2c_reg);
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, i2c_dev | 0x01);
    res = I2C_read(I2C_NUMBER, 0x00);
    I2C_stop(I2C_NUMBER);
    return res;
}

void I2C_writechar(uint8_t I2C_NUMBER, uint8_t i2c_dev, uint8_t i2c_reg, uint8_t i2c_val)
{
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, i2c_dev);
    I2C_write(I2C_NUMBER, i2c_reg);
    I2C_write(I2C_NUMBER, i2c_val);
    I2C_stop(I2C_NUMBER);
}
