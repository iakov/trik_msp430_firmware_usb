/*
 * trik_mcp3424.c
 *
 *  Created on: April 6, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_mcp3424.h"
#include "trik_softi2c.h"
#include "trik_devices.h"

// MCP3424 read channel 1
uint32_t MCP3424_read_ch1(uint8_t I2C_NUMBER)
{
    uint32_t ttt1, ttt2, ttt3;
	// Config
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0);
    I2C_write(I2C_NUMBER, 0b10011100);
    I2C_stop(I2C_NUMBER);
    // Read
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0 | 0x01);
    ttt1 = I2C_read(I2C_NUMBER, 0x01);
    ttt2 = I2C_read(I2C_NUMBER, 0x01);
    ttt3 = I2C_read(I2C_NUMBER, 0x01);
    I2C_read(I2C_NUMBER, 0x00);
    I2C_stop(I2C_NUMBER);
	return ttt3 + (ttt2 << 8) + ((ttt1 & 0b11) << 16);
}

// MCP3424 read channel 2
uint32_t MCP3424_read_ch2(uint8_t I2C_NUMBER)
{
    uint32_t ttt1, ttt2, ttt3;
	// Config
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0);
    I2C_write(I2C_NUMBER, 0b10111100);
    I2C_stop(I2C_NUMBER);
    // Read
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0 | 0x01);
    ttt1 = I2C_read(I2C_NUMBER, 0x01);
    ttt2 = I2C_read(I2C_NUMBER, 0x01);
    ttt3 = I2C_read(I2C_NUMBER, 0x01);
    I2C_read(I2C_NUMBER, 0x00);
    I2C_stop(I2C_NUMBER);
    return ttt3 + (ttt2 << 8) + ((ttt1 & 0b11) << 16);
}

// MCP3424 read channel 3
uint32_t MCP3424_read_ch3(uint8_t I2C_NUMBER)
{
    uint32_t ttt1, ttt2, ttt3;
	// Config
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0);
    I2C_write(I2C_NUMBER, 0b11011100);
    I2C_stop(I2C_NUMBER);
    // Read
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0 | 0x01);
    ttt1 = I2C_read(I2C_NUMBER, 0x01);
    ttt2 = I2C_read(I2C_NUMBER, 0x01);
    ttt3 = I2C_read(I2C_NUMBER, 0x01);
    I2C_read(I2C_NUMBER, 0x00);
    I2C_stop(I2C_NUMBER);
    return ttt3 + (ttt2 << 8) + ((ttt1 & 0b11) << 16);
}

// MCP3424 read channel 4
uint32_t MCP3424_read_ch4(uint8_t I2C_NUMBER)
{
    uint32_t ttt1, ttt2, ttt3;
	// Config
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0);
    I2C_write(I2C_NUMBER, 0b11111100);
    I2C_stop(I2C_NUMBER);
    // Read
    I2C_start(I2C_NUMBER);
    I2C_write(I2C_NUMBER, 0xD0 | 0x01);
    ttt1 = I2C_read(I2C_NUMBER, 0x01);
    ttt2 = I2C_read(I2C_NUMBER, 0x01);
    ttt3 = I2C_read(I2C_NUMBER, 0x01);
    I2C_read(I2C_NUMBER, 0x00);
    I2C_stop(I2C_NUMBER);
    return ttt3 + (ttt2 << 8) + ((ttt1 & 0b11) << 16);
}
