/*
 * Trik_ProtocolHandler.h
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_PROTOCOLHANDLER_H_
#define TRIK_PROTOCOLHANDLER_H_

#define MAX_STRING_LENGTH 32

//Error defines
#define NO_ERROR 0x00
#define FUNC_CODE_ERROR 0x01
#define REG_ADDR_ERROR 0x02
#define REG_VAL_ERROR 0x03
#define SLAVE_ERROR 0x04
#define SLAVE_BUSY 0x06
#define DEV_ADDR_ERROR 0x11
#define CRC_ERROR 0x12
#define START_ERROR 0x13
#define LENGTH_ERROR 0x14
#define UNDEF_ERROR 0xFF

//Functions numbers
#define FUNCx03 0x03
#define FUNCx04 0x04
#define FUNCx05 0x05
#define FUNCx06 0x06

//Register size
#define REG_16bits 0
#define REG_32bits 1

//Protocol handler
uint8_t PROTOCOL_hadler(char *in_str, char *out_str);

//Response function
void PROTOCOL_transResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code);
void PROTOCOL_recvResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code, uint8_t reg_addr, uint32_t reg_val, uint8_t reg_size);
void PROTOCOL_errResponse(char *r_str, uint8_t dev_addr, uint8_t func_code, uint8_t err_code);

#endif /* TRIK_PROTOCOLHANDLER_H_ */
