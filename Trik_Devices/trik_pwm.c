/*
 * trik_pwm.c
 *
 *  Created on: January 28, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_pwm.h"

//PWM enable and start
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
                TA1CCR0 = PWM[PWM_NUMBER-PWM1].PPER;           // PWM Period
                TA1CCR1 = PWM[PWM_NUMBER-PWM1].PDUT;           // CCR1 PWM duty cycle
                break;
            case PWM2:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4);*/
                P2SEL |= BIT4;
                P2DIR |= BIT4;
                //PWM timer
                TA2CCR0 = PWM[PWM_NUMBER-PWM1].PPER;           // PWM Period
                TA2CCR1 = PWM[PWM_NUMBER-PWM1].PDUT;           // CCR1 PWM duty cycle
                break;
            case PWM3:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5);*/
                P2SEL |= BIT5;
                P2DIR |= BIT5;
                //PWM timer
                TA2CCR0 = PWM[PWM_NUMBER-PWM1].PPER;           // PWM Period
                TA2CCR2 = PWM[PWM_NUMBER-PWM1].PDUT;           // CCR2 PWM duty cycle
                break;
            case PWM4:
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN1);*/
                P2SEL |= BIT1;
                P2DIR |= BIT1;
                //PWM timer
                TA1CCR0 = PWM[PWM_NUMBER-PWM1].PPER;           // PWM Period
                TA1CCR2 = PWM[PWM_NUMBER-PWM1].PDUT;           // CCR2 PWM duty cycle
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
            P2SEL &= ~BIT4;
            P2DIR &= ~BIT4;
            break;
        case PWM3:
            P2SEL &= ~BIT5;
            P2DIR &= ~BIT5;
            break;
        case PWM4:
            P2SEL &= ~BIT1;
            P2DIR &= ~BIT1;
            break;
        default:
            break;
    }
}

//Handler
void PWM_handler(uint8_t PWM_NUMBER)
{
    //Enable (start) / disable
    if (PWM[PWM_NUMBER-PWM1].PCTL & PWM_ENABLE)
        PWM_enable(PWM_NUMBER);
    else
        PWM_disable(PWM_NUMBER);

    PWM[PWM_NUMBER-PWM1].PSTA = PWM_NO_ERROR;
}


