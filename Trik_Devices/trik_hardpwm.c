/*
 * trik_hardpwm.c
 *
 *  Created on: January 28, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_hardpwm.h"
#include "trik_devices.h"

// PWM enable and start
void HPWM_enable(uint8_t HPWM_NUMBER)
{
        switch (HPWM_NUMBER)
        {
            case HPWM1:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0);*/
                P2SEL |= BIT0;
                P2DIR |= BIT0;
                //PWM timer
                TA1CCR0 = HPWM[HPWM_NUMBER-HPWM1].HPPER;           // PWM Period
                TA1CCR1 = HPWM[HPWM_NUMBER-HPWM1].HPDUT;           // CCR1 PWM duty cycle
                break;
            case HPWM2:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4);*/
                P2SEL |= BIT4;
                P2DIR |= BIT4;
                //PWM timer
                TA2CCR0 = HPWM[HPWM_NUMBER-HPWM1].HPPER;           // PWM Period
                TA2CCR1 = HPWM[HPWM_NUMBER-HPWM1].HPDUT;           // CCR1 PWM duty cycle
                break;
            case HPWM3:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5);*/
                P2SEL |= BIT5;
                P2DIR |= BIT5;
                //PWM timer
                TA2CCR0 = HPWM[HPWM_NUMBER-HPWM1].HPPER;           // PWM Period
                TA2CCR2 = HPWM[HPWM_NUMBER-HPWM1].HPDUT;           // CCR2 PWM duty cycle
                break;
            case HPWM4:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN1);*/
                P2SEL |= BIT1;
                P2DIR |= BIT1;
                //PWM timer
                TA1CCR0 = HPWM[HPWM_NUMBER-HPWM1].HPPER;           // PWM Period
                TA1CCR2 = HPWM[HPWM_NUMBER-HPWM1].HPDUT;           // CCR2 PWM duty cycle
                break;
            default:
                break;
        }
}

// PWM disable
void HPWM_disable(uint8_t HPWM_NUMBER)
{
    switch (HPWM_NUMBER)
    {
        case HPWM1:
            P2SEL &= ~BIT0;
            P2DIR &= ~BIT0;
            break;
        case HPWM2:
            P2SEL &= ~BIT4;
            P2DIR &= ~BIT4;
            break;
        case HPWM3:
            P2SEL &= ~BIT5;
            P2DIR &= ~BIT5;
            break;
        case HPWM4:
            P2SEL &= ~BIT1;
            P2DIR &= ~BIT1;
            break;
        default:
            break;
    }
}
