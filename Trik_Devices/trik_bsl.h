/*
 * trick_bsl.h
 *
 *  Created on: October 27, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRICK_BSL_H_
#define TRICK_BSL_H_

#define PSWD_OK 0x00
#define PSWD_FAIL 0x01

//API functions
uint8_t BSL_enterBSL(uint32_t bslpswd);

#endif /* TRICK_BSL_H_ */
