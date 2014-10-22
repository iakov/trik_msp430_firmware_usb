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

#endif /* TRIK_PROTOCOLHANDLER_H_ */
