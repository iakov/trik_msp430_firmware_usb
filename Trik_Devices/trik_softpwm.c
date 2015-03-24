/*
 * trik_softpwm.c
 *
 *  Created on: March 24, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_softpwm.h"

//SPWM enable and start
void SPWM_enable(uint8_t SPWM_NUMBER)
{
    if (!(isSlotBusy(SPWM_NUMBER)))
    {
        reseveSlot(SPWM_NUMBER);
        switch (SPWM_NUMBER)
        {
            case SPWM1:
                P2SEL &= ~BIT0;
                P2DIR |= BIT0;
                break;
            case SPWM2:
                P2SEL &= ~BIT3;
                P2DIR |= BIT3;
                break;
            case SPWM3:
                P2SEL &= ~BIT4;
                P2DIR |= BIT4;
                break;
            case SPWM4:
                P1SEL &= ~BIT0;
                P1DIR |= BIT0;
                break;
            case SPWM5:
                P2SEL &= ~BIT1;
                P2DIR |= BIT1;
                break;
            case SPWM6:
                P1SEL &= ~BIT6;
                P1DIR |= BIT6;
                break;
            case SPWM7:
                P2SEL &= ~BIT5;
                P2DIR |= BIT5;
                break;
            case SPWM8:
                P2SEL &= ~BIT2;
                P2DIR |= BIT2;
                break;
            case SPWM9:
                P4DIR &= ~BIT5;
                P6SEL &= ~BIT5;
                P6DIR |= BIT5;
                break;
            case SPWM10:
                P4DIR &= ~BIT4;
                P6SEL &= ~BIT4;
                P6DIR |= BIT4;
                break;
            case SPWM11:
                P4DIR &= ~BIT3;
                P6SEL &= ~BIT3;
                P6DIR |= BIT3;
                break;
            case SPWM12:
                P4DIR &= ~BIT2;
                P6SEL &= ~BIT2;
                P6DIR |= BIT2;
                break;
            case SPWM13:
                P3DIR &= ~BIT2;
                P6SEL &= ~BIT1;
                P6DIR |= BIT1;
                break;
            case SPWM14:
                P3DIR &= ~BIT4;
                P6SEL &= ~BIT0;
                P6DIR |= BIT0;
                break;
            default:
                break;
        }
    }
}

//SPWM disable
void SPWM_disable(uint8_t SPWM_NUMBER)
{
    releaseSlot(SPWM_NUMBER);
    switch (SPWM_NUMBER)
    {
        case SPWM1:
            P2DIR &= ~BIT0;
            break;
        case SPWM2:
            P2DIR &= ~BIT3;
            break;
        case SPWM3:
            P2DIR &= ~BIT4;
            break;
        case SPWM4:
            P1DIR &= ~BIT0;
            break;
        case SPWM5:
            P2DIR &= ~BIT1;
            break;
        case SPWM6:
            P1DIR &= ~BIT6;
            break;
        case SPWM7:
            P2DIR &= ~BIT5;
            break;
        case SPWM8:
            P2DIR &= ~BIT2;
            break;
        case SPWM9:
            P6DIR &= ~BIT5;
            break;
        case SPWM10:
            P6DIR &= ~BIT4;
            break;
        case SPWM11:
            P6DIR &= ~BIT3;
            break;
        case SPWM12:
            P6DIR &= ~BIT2;
            break;
        case SPWM13:
            P6DIR &= ~BIT1;
            break;
        case SPWM14:
            P6DIR &= ~BIT0;
            break;
        default:
            break;
    }
}

