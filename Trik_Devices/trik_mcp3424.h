/*
 * trik_mcp3424.h
 *
 *  Created on: April 6, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_DEVICES_TRIK_MCP3424_H_
#define TRIK_DEVICES_TRIK_MCP3424_H_

uint32_t MCP3424_read_ch1(uint8_t I2C_NUMBER);
uint32_t MCP3424_read_ch2(uint8_t I2C_NUMBER);
uint32_t MCP3424_read_ch3(uint8_t I2C_NUMBER);
uint32_t MCP3424_read_ch4(uint8_t I2C_NUMBER);

#endif /* TRIK_DEVICES_TRIK_MCP3424_H_ */
