/*
 * Trik_ProtocolHandler.h
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_PROTOCOLHANDLER_H_
#define TRIK_PROTOCOLHANDLER_H_

#define MAX_STRING_LENGTH   32

#define False               0x00
#define True                0x01

// Error defines
#define NO_ERROR            0x00
#define FUNC_CODE_ERROR     0x01
#define REG_ADDR_ERROR      0x02
#define REG_VAL_ERROR       0x03
#define SLAVE_ERROR         0x04
#define SLAVE_BUSY          0x06
#define DEV_ADDR_ERROR      0x11
#define CRC_ERROR           0x12
#define START_ERROR         0x13
#define LENGTH_ERROR        0x14
#define REG_INC_ERROR       0x15
#define BUFFER_ERROR        0x33
#define DEV_EN_ERROR        0x34
#define UNDEF_ERROR         0xFF

// Functions numbers
#define FUNC_WRITE          0x03
#define FUNC_READ           0x05

// Register size
#define REG_16bits          0x00
#define REG_32bits          0x01

// HEX number sizes
#define NUM_BYTE            0x02
#define NUM_WORD            0x04
#define NUM_DWORD           0x08

// Protocol handler
uint8_t PROTOCOL_handler(char *in_str, char *out_str);

// Response functions
void PROTOCOL_recvResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code, uint8_t reg_addr, uint32_t reg_val);

// 1 byte number to string hex
uint8_t TO_HEX(uint8_t i);
void char2hex(char *string, uint8_t number);

// String HEX to N bytes number
uint32_t hex2num(char *string, uint16_t pos, uint16_t numsize);

// Function to find terminate char in string
uint8_t retInString (char* string);

#endif /* TRIK_PROTOCOLHANDLER_H_ */
