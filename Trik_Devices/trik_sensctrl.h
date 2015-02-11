/*
 * trik_sensctrl.h
 *
 *  Created on: Fabruary 11, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SENSCTRL_H_
#define TRIK_SENSCTRL_H_

// Sensor control register
#define SPPCTL              0x00

// Sensor control errors
#define SPCTL_NO_ERROR      0x00

// Masks for bits of control register
#define SPCTL_ENABLE        0x8000 //SPCTL enable
#define JA1_ON              0x0002 //JA1 on
#define JA2_ON              0x0004 //JA2 on
#define JA3_ON              0x0008 //JA3 on
#define JA4_ON              0x0010 //JA4 on
#define JA5_ON              0x0020 //JA5 on
#define JA6_ON              0x0040 //JA6 on

// Prototypes for the APIs
void SPCTL_handler();
void SPCTL_pin_on(uint8_t PIN_NUMBER);
void SPCTL_pin_off(uint8_t PIN_NUMBER);

// Sensor control register
volatile uint16_t SPCTL;


#endif /* TRIK_SENSCTRL_H_ */
