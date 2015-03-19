/*
 * trik_regaccess.h
 *
 *  Imported from driverlib: Fabruary 4, 2015
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

#endif /* TRIK_REGACCESS_H_ */
