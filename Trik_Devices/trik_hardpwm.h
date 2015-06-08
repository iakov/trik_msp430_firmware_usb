/*
 * trik_pwm.h
 *
 *  Created on: January 28, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_PWM_H_
#define TRIK_PWM_H_

//PWM registers
#define PPCTL               0x00
#define PPDUT               0x01
#define PPPER               0x02
#define PPVER               0x03

//PWM errors
#define PWM_NO_ERROR        0x00

//Masks for bits of control register
#define PWM_ENABLE          0x8000 //PWM enable

//Max PWMs
#define MAX_PWMS            0x05

//Prototypes for the APIs
void PWM_handler(uint8_t PWM_NUMBER);
void PWM_enable(uint8_t PWM_NUMBER);
void PWM_disable(uint8_t PWM_NUMBER);

//PWM registers
struct tPWMRegisters
{
    uint16_t PCTL;
    uint16_t PDUT;
    uint32_t PSTA;
    uint16_t PPER;
};

//PWM registers array
volatile struct tPWMRegisters PWM[MAX_PWMS];

#endif /* TRIK_PWM_H_ */
