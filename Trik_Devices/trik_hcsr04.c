/*
 * trik_hcsr04.c
 *
 *  Created on: August 20, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_hcsr04.h"
#include "trik_sensor.h"
#include "trik_devices.h"
#include "trik_async.h"

uint32_t HCSR_read(uint8_t SENS_NUMBER)
{
	uint32_t cnt1 = 0;
	uint8_t pin_echo = BIT0;
	uint8_t pin_trig = BIT0;

	switch (SENS_NUMBER)
	{
		case SENSOR1:
			pin_echo = BIT5;
			pin_trig = BIT5;
			break;
		case SENSOR2:
			pin_echo = BIT4;
			pin_trig = BIT4;
			break;
		case SENSOR3:
			pin_echo = BIT3;
			pin_trig = BIT3;
			break;
		case SENSOR4:
			pin_echo = BIT2;
			pin_trig = BIT2;
			break;
		case SENSOR5:
			pin_echo = BIT1;
			pin_trig = BIT2;
			break;
		case SENSOR6:
			pin_echo = BIT0;
			pin_trig = BIT4;
			break;
		case SENSOR7:
			pin_echo = BIT3;
			pin_trig = BIT0;
			break;
		case SENSOR8:
			pin_echo = BIT3;
			pin_trig = BIT0;
			break;
		case SENSOR9:
			pin_echo = BIT0;
			pin_trig = BIT4;
			break;
		case SENSOR10:
			pin_echo = BIT0;
			pin_trig = BIT4;
			break;
		case SENSOR11:
			pin_echo = BIT2;
			pin_trig = BIT5;
			break;
		case SENSOR12:
			pin_echo = BIT2;
			pin_trig = BIT5;
			break;
		case SENSOR13:
			pin_echo = BIT6;
			pin_trig = BIT1;
			break;
		case SENSOR14:
			pin_echo = BIT6;
			pin_trig = BIT1;
			break;
		default:
	    	return HCSR_SENS_NUM;
	}

	if ((SENS_NUMBER >= SENSOR1) && (SENS_NUMBER <= SENSOR4))
	{
		P6SEL &= ~pin_echo;
		P4SEL &= ~pin_trig;
		P6REN &= ~pin_echo;
		P4REN &= ~pin_trig;
		P6OUT &= ~pin_echo;
		P4OUT &= ~pin_trig;
		P6DIR &= ~pin_echo;
		P4DIR |= pin_trig;

		// Send trigger signal
		P4OUT |= pin_trig;
		__delay_cycles(WAIT_15_US);
		P4OUT &= ~pin_trig;

		// Wait before receiving echo signal
		__delay_cycles(WAIT_15_US);
		__delay_cycles(WAIT_15_US);
		__delay_cycles(WAIT_15_US);

		// Wait for echo signal
		while (!(P6IN & pin_echo))
		{
			__delay_cycles(WAIT_1_US); cnt1 ++;
			if (cnt1 > 50000)
				return HCSR_NO_RESPONSE;
		}
	}

	// Wait 60 ms for whole measurement cycle
	__delay_cycles(WAIT_60_MS);

	return cnt1;
}

