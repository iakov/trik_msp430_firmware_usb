/*
 * trik_sensctrl.c
 *
 *  Created on: Fabruary 11, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_sensctrl.h"

void SPCTL_handler()
{
    //Enable / disable
    if (SPCTL & SPCTL_ENABLE)
        if (!(isSlotBusy(SENSCTRL)))
        {
            reseveSlot(SENSCTRL);
            if (SPCTL & JA1_ON)
            {
                P4OUT |= BIT5;
                P4DIR |= BIT5;
            }
            else
            {
                P4OUT &= ~BIT5;
                P4DIR |= BIT5;
            }
            if (SPCTL & JA2_ON)
            {
                P4OUT |= BIT4;
                P4DIR |= BIT4;
            }
            else
            {
                P4OUT &= ~BIT4;
                P4DIR |= BIT4;
            }
            if (SPCTL & JA3_ON)
            {
                P4OUT |= BIT3;
                P4DIR |= BIT3;
            }
            else
            {
                P4OUT &= ~BIT3;
                P4DIR |= BIT3;
            }
            if (SPCTL & JA4_ON)
            {
                P4OUT |= BIT2;
                P4DIR |= BIT2;
            }
            else
            {
                P4OUT &= ~BIT2;
                P4DIR |= BIT2;
            }
            if (SPCTL & JA5_ON)
            {
                P3OUT |= BIT2;
                P3DIR |= BIT2;
            }
            else
            {
                P3OUT &= ~BIT2;
                P3DIR |= BIT2;
            }
            if (SPCTL & JA6_ON)
            {
                P3OUT |= BIT4;
                P3DIR |= BIT4;
            }
            else
            {
                P3OUT &= ~BIT4;
                P3DIR |= BIT4;
            }
        }
    else
    {
        releaseSlot(SENSCTRL);
        P4OUT &= ~(BIT2+BIT3+BIT4+BIT5);
        P3OUT &= ~(BIT2+BIT4);
        P4DIR &= ~(BIT2+BIT3+BIT4+BIT5);
        P3DIR &= ~(BIT2+BIT4);
    }

    SPSTA = SPCTL_NO_ERROR;
}

