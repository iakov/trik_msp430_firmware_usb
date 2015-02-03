/*
 * trik_pwm.c
 *
 *  Created on: January 28, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_devices.h"
#include "trik_pwm.h"
#include "driverlib.h"

//Motor enable and start
void PWM_enable(uint8_t PWM_NUMBER)
{
    if (!(isSlotBusy(PWM_NUMBER)))
    {
        reseveSlot(PWM_NUMBER);
        switch (PWM_NUMBER)
        {
            case PWM1:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0);*/
                P2SEL |= BIT0;
                P2DIR |= BIT0;
                //PWM timer
                TA1CCR0 = PWM[PWM_NUMBER].PPER;           // PWM Period
                TA1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
                TA1CCR1 = PWM[PWM_NUMBER].PDUT;           // CCR1 PWM duty cycle
                TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR, divider - 8
                break;
            case PWM2: //????????????????????????????????????????????????????
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN3);*/
                P2SEL |= BIT3;
                P2DIR |= BIT3;
                //PWM timer
                TA2CCR0 = PWM[PWM_NUMBER].PPER;           // PWM Period
                TA2CCTL0 = OUTMOD_7;                      // CCR1 reset/set
                TA2CCR0 = PWM[PWM_NUMBER].PDUT;           // CCR1 PWM duty cycle
                TA2CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR, divider - 8
                break;
            case PWM3:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4);*/
                P2SEL |= BIT4;
                P2DIR |= BIT4;
                //PWM timer
                TA2CCR0 = PWM[PWM_NUMBER].PPER;           // PWM Period
                TA2CCTL1 = OUTMOD_7;                      // CCR1 reset/set
                TA2CCR1 = PWM[PWM_NUMBER].PDUT;           // CCR1 PWM duty cycle
                TA2CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR, divider - 8
                break;
            case PWM4:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5);*/
                P2SEL |= BIT5;
                P2DIR |= BIT5;
                //PWM timer
                TA2CCR0 = PWM[PWM_NUMBER].PPER;           // PWM Period
                TA2CCTL2 = OUTMOD_7;                      // CCR2 reset/set
                TA2CCR2 = PWM[PWM_NUMBER].PDUT;           // CCR2 PWM duty cycle
                TA2CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR, divider - 8
                break;
            case PWM5:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN1);*/
                P2SEL |= BIT1;
                P2DIR |= BIT1;
                //PWM timer
                TA1CCR0 = PWM[PWM_NUMBER].PPER;           // PWM Period
                TA1CCTL2 = OUTMOD_7;                      // CCR2 reset/set
                TA1CCR2 = PWM[PWM_NUMBER].PDUT;           // CCR2 PWM duty cycle
                TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR, divider - 8
                break;
            default:
                break;
        }
    }
}

//PWM disable
void PWM_disable(uint8_t PWM_NUMBER)
{
    releaseSlot(PWM_NUMBER);
    switch (PWM_NUMBER)
    {
        case PWM1:
            P2SEL &= ~BIT0;
            P2DIR &= ~BIT0;
            break;
        case PWM2:
            P2SEL &= ~BIT3;
            P2DIR &= ~BIT3;
            break;
        case PWM3:
            P2SEL &= ~BIT4;
            P2DIR &= ~BIT4;
            break;
        case PWM4:
            P2SEL &= ~BIT5;
            P2DIR &= ~BIT5;
            break;
        case PWM5:
            P2SEL &= ~BIT1;
            P2DIR &= ~BIT1;
            break;
        default:
            break;
    }
}



