/*
 * Trik_ProtocolHandler.h
 *
 *  Created on: 21 окт. 2014 г.
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_PROTOCOLHANDLER_H_
#define TRIK_PROTOCOLHANDLER_H_

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 32

//Protocol handler
uint8_t PROTOCOL_hadler(char *in_str, char *out_str);

//Response function
void PROTOCOL_transResponse(char *r_str, uint8_t dev_addr, uint8_t resp_code);
void PROTOCOL_recvResponse(char *r_str, uint8_t dev_addr, uint8_t func_code, uint8_t reg_addr, uint32_t reg_val);
void PROTOCOL_errResponse(char *r_str, uint8_t dev_addr, uint8_t func_code, uint8_t err_code);

#endif /* TRIK_PROTOCOLHANDLER_H_ */
