/*
 * trik_sc16is7x0.c
 *
 *  Created on: May 26, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_softi2c.h"
#include "trik_devices.h"
#include "trik_sc16is7x0.h"

void USART_write_reg(uint8_t USART_NUMBER, uint8_t regaddr, uint8_t regval)
{
	I2C_writechar(USART_NUMBER - USART1 + I2C1, SC16IS7X0_ADDR, regaddr << 3, regval);
}

uint8_t USART_read_reg(uint8_t USART_NUMBER, uint8_t regaddr)
{
	return I2C_readchar(USART_NUMBER - USART1 + I2C1, SC16IS7X0_ADDR, regaddr << 3);
}

void USART_config(uint8_t USART_NUMBER, uint32_t cfg_bits)
{
	uint8_t cfg1 = 0;
	// FCR register - enable and clear FIFO
	USART_write_reg(USART_NUMBER, 0x02, 0b00000111);
	// Enable write to EFR register
	USART_write_reg(USART_NUMBER, 0x03, 0xBF);
	// EFR register - enable enhanced functions
	cfg1 = 0b00010000;
	USART_write_reg(USART_NUMBER, 0x02, cfg1);
	// Disable write to EFR register
	USART_write_reg(USART_NUMBER, 0x03, 0x00);
	// MCR register
	cfg1 = 0;
	if (cfg_bits & USART_IRDA1) cfg1 |= 0b01000000;
	if (cfg_bits & USART_IRDA2) cfg1 |= 0b01000000;
	if (cfg_bits & USART_RTS) cfg1 |= 0b00000010;
	if (cfg_bits & USART_DTR) cfg1 |= 0b00000001;
	USART_write_reg(USART_NUMBER, 0x04, cfg1);
	// EFCR register
	cfg1 = 0;
	if (cfg_bits & USART_IRDA2) cfg1 |= 0b10000000;
	if (cfg_bits & USART_INVRTS) cfg1 |= 0b00100000;
	if (cfg_bits & USART_RS485) cfg1 |= 0b00010000;
	if (cfg_bits & USART_RS485M) cfg1 |= 0b00010001;
	if (!(cfg_bits & USART_RXEN)) cfg1 |= 0b00000010;
	if (!(cfg_bits & USART_TXEN)) cfg1 |= 0b00000100;
	USART_write_reg(USART_NUMBER, 0x0F, cfg1);
	// LCR register
	cfg1 = 0;
	if (cfg_bits & USART_ODD) cfg1 |= 0b00001000;
	if (cfg_bits & USART_EVEN) cfg1 |= 0b00011000;
	if (cfg_bits & USART_2SB) cfg1 |= 0b00000100;
	if (cfg_bits & USART_6BITS) cfg1 |= 0b00000001;
	if (cfg_bits & USART_7BITS) cfg1 |= 0b00000010;
	if (cfg_bits & USART_8BITS) cfg1 |= 0b00000011;
	USART_write_reg(USART_NUMBER, 0x03, cfg1);
}

void USART_set_speed(uint8_t USART_NUMBER, uint32_t baud_rate)
{
	uint32_t usart_div = 0;
	uint8_t cfg1 = 0;
	if ((baud_rate < 50) || (baud_rate > 56000))
		baud_rate = 50;
	usart_div = 1843200 / (baud_rate * 16);
	cfg1 = USART_read_reg(USART_NUMBER, 0x03);
	USART_write_reg(USART_NUMBER, 0x03, cfg1 | 0x80);
	USART_write_reg(USART_NUMBER, 0x00, (uint8_t)(usart_div & 0xFF));
	USART_write_reg(USART_NUMBER, 0x01, (uint8_t)((usart_div >> 8) & 0xFF));
	USART_write_reg(USART_NUMBER, 0x03, cfg1);
}

void USART_reset(uint8_t USART_NUMBER)
{
	USART_write_reg(USART_NUMBER, 0x0E, 0b00001000);
}
