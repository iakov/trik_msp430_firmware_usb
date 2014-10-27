/*
 * trick_bsl.h
 *
 *  Created on: 27 окт. 2014 г.
 *      Author: Rostislav Varzar
 */

#ifndef TRICK_BSL_H_
#define TRICK_BSL_H_

#include <stdint.h>
#include "trik_devices.h"

#define PSWD_OK 0x00
#define PSWD_FAIL 0x01

//API functions
uint8_t BSL_enterBSL(uint32_t bslpswd);

#endif /* TRICK_BSL_H_ */
