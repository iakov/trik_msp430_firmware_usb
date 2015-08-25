/*
 * trik_hcsr04.h
 *
 *  Created on: August 20, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_DEVICES_TRIK_HCSR04_H_
#define TRIK_DEVICES_TRIK_HCSR04_H_

// Defines for HCSR04 errors
#define HCSR_NO_ERROR		0x00000000
#define HCSR_NO_RESPONSE	0xAAAAAAAA
#define HCSR_DIST_ERR		0xBBBBBBBB
#define HCSR_SENS_NUM		0xCCCCCCCC
#define HCSR_MAIN_ERROR		0xFFFFFFFF

// Defines for time delays, 1 us = 14.4 cycles
#define WAIT_1_US			14
#define WAIT_2_US			28
#define WAIT_5_US			72
#define WAIT_10_US			144
#define WAIT_20_US			288
#define WAIT_15_US			216
#define WAIT_60_MS			864000

uint32_t HCSR04_read(uint8_t SENS_NUMBER);
uint32_t HCSR04_get_time_us(uint8_t SENS_NUMBER);

#endif /* TRIK_DEVICES_TRIK_HCSR04_H_ */
