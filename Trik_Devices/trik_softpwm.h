/*
 * trik_softpwm.h
 *
 *  Created on: March 24, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SOFTPWM_H_
#define TRIK_SOFTPWM_H_

//SPWM registers
#define SPPCTL              0x00
#define SPPDUT              0x01
#define SPPPER              0x02
#define SPPVER              0x03

//SPWM errors
#define SPWM_NO_ERROR       0x00

//Masks for bits of control register
#define SPWM_ENABLE         0x8000 //SPWM enable

//SMax PWMs
#define MAX_SPWMS           0x0E

//Prototypes for the APIs
void SPWM_handler(uint8_t SPWM_NUMBER);
void SPWM_enable(uint8_t SPWM_NUMBER);
void SPWM_disable(uint8_t SPWM_NUMBER);

//SPWM registers
struct tSPWMRegisters
{
    uint16_t SPCTL;
    uint16_t SPDUT;
    uint32_t SPSTA;
    uint16_t SPPER;
};

//Software PWM registers array
volatile struct tSPWMRegisters SPWM[MAX_SPWMS];

#endif /* TRIK_SOFTPWM_H_ */
