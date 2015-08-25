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

uint32_t HCSR04_read(uint8_t SENS_NUMBER)
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

	if ((SENS_NUMBER == SENSOR7) || (SENS_NUMBER == SENSOR8) || (SENS_NUMBER == SENSOR11) || (SENS_NUMBER == SENSOR12))
	{
		P2SEL &= ~pin_echo;
		P2SEL &= ~pin_trig;
		P2REN &= ~pin_echo;
		P2REN &= ~pin_trig;
		P2OUT &= ~pin_echo;
		P2OUT &= ~pin_trig;
		P2DIR &= ~pin_echo;
		P2DIR |= pin_trig;

		// Send trigger signal
		P2OUT |= pin_trig;
		__delay_cycles(WAIT_10_US);
		P2OUT &= ~pin_trig;

		// Waiting for echo signal
		while (!(P2IN & pin_echo))
		{
			__delay_cycles(WAIT_20_US); cnt1 ++;
			if (cnt1 > 5000)
				return HCSR_NO_RESPONSE;
		}

		// Counting duration
		cnt1 = 0;
		while (P2IN & pin_echo)
		{
			__delay_cycles(WAIT_20_US); cnt1 ++;
			if (cnt1 > 5000)
				return HCSR_DIST_ERR;
		}

	}
	else if ((SENS_NUMBER == SENSOR9) || (SENS_NUMBER == SENSOR10) || (SENS_NUMBER == SENSOR13) || (SENS_NUMBER == SENSOR14))
	{
		P1SEL &= ~pin_echo;
		P2SEL &= ~pin_trig;
		P1REN &= ~pin_echo;
		P2REN &= ~pin_trig;
		P1OUT &= ~pin_echo;
		P2OUT &= ~pin_trig;
		P1DIR &= ~pin_echo;
		P2DIR |= pin_trig;

		// Send trigger signal
		P2OUT |= pin_trig;
		__delay_cycles(WAIT_10_US);
		P2OUT &= ~pin_trig;

		// Waiting for echo signal
		while (!(P1IN & pin_echo))
		{
			__delay_cycles(WAIT_1_US); cnt1 ++;
			if (cnt1 > 100000)
				return HCSR_NO_RESPONSE;
		}

		// Counting duration
		cnt1 = 0;
		while (P1IN & pin_echo)
		{
			__delay_cycles(WAIT_1_US); cnt1 ++;
			if (cnt1 > 100000)
				return HCSR_DIST_ERR;
		}

	}
	else
	{
		return HCSR_SENS_NUM;
	}

	return cnt1;
}

uint32_t HCSR04_get_time_us(uint8_t SENS_NUMBER)
{
	uint32_t hcsr04_result;
	disableTimer_B();
	hcsr04_result = HCSR04_read(SENS_NUMBER);
	enableTimer_B();
	__delay_cycles(WAIT_60_MS);
	if (hcsr04_result < 25000)
	{
		return hcsr04_result;
	}
	else
	{
		return HCSR_MAIN_ERROR;
	}
}

