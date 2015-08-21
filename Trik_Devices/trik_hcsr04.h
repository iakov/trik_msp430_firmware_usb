/*
 * trik_hcsr04.h
 *
 *  Created on: August 20, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_DEVICES_TRIK_HCSR04_H_
#define TRIK_DEVICES_TRIK_HCSR04_H_

// Defines for HCSR04 errors
#define HCSR_NO_ERROR		0x00
#define HCSR_NO_RESPONSE	0xAAAAAAAA
#define HCSR_SENS_NUM		0xBBBBBBBB
#define HCSR_MAIN_ERROR		0xFFFFFFFF

// Defines for time delays, 1 us = 14.4 cycles
#define WAIT_1_US			14
#define WAIT_10_US			144
#define WAIT_15_US			216
#define WAIT_100_US			1440
#define WAIT_1_MS			14400
#define WAIT_60_MS			864000

uint32_t HCSR_read(uint8_t SENS_NUMBER);

#endif /* TRIK_DEVICES_TRIK_HCSR04_H_ */
