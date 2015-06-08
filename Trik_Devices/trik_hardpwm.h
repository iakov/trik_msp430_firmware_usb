/*
 * trik_hardpwm.h
 *
 *  Created on: January 28, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_HARDPWM_H_
#define TRIK_HARDPWM_H_

// PWM registers
#define HPPCTL				0x00
#define HPPDUT				0x01
#define HPPPER				0x02
#define HPPVER				0x03

// PWM errors
#define HPWM_NO_ERROR		0x00

// Masks for bits of control register
#define HPWM_ENABLE			0x8000 // HPWM enable

// Max HPWMs
#define MAX_HPWMS			0x04

// Prototypes for hardware PWM functions
void HPWM_enable(uint8_t HPWM_NUMBER);
void HPWM_disable(uint8_t HPWM_NUMBER);

// PWM registers
struct tHPWMRegisters
{
    uint16_t HPCTL;
    uint16_t HPDUT;
    uint32_t HPSTA;
    uint16_t HPPER;
};

// PWM registers array
volatile struct tHPWMRegisters HPWM[MAX_HPWMS];

#endif /* TRIK_HARDPWM_H_ */
