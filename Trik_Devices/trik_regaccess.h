/*
 * trik_regaccess.h
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_REGACCESS_H_
#define TRIK_REGACCESS_H_

#define HWREG32(x)                                                              \
        (*((volatile uint32_t*)((uint16_t)x)))
#define HWREG16(x)                                                             \
        (*((volatile uint16_t*)((uint16_t)x)))
#define HWREG8(x)                                                             \
        (*((volatile uint8_t*)((uint16_t)x)))

#define STATUS_SUCCESS  0x01
#define STATUS_FAIL     0x00

#define bool   _Bool
#define false  0
#define true   1

#endif /* TRIK_REGACCESS_H_ */
