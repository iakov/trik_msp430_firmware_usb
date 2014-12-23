/*
 * trik_async.c
 *
 *  Created on: November 11, 2014
 *      Author: Rostislav Varzar
 */

#include "driverlib.h"
#include "trik_devices.h"
#include "trik_async.h"

//Init timer B for asynchronous packets
void enableTimer_B()
{
    reseveSlot(ASYNCTIMER);
    //Overflow interrupt frequency is 10 kHz
    TB0CTL &= ~TBIFG; //TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
    TB0CTL &= ~ID__8;
    TB0EX0 = TBIDEX_0;
    TBCCR0 = NORMAL_PERIOD;
    TB0CTL = MC_1 + TBCLR + ID__1 + TBIE + TBSSEL_2;
}

void disableTimer_B()
{
    releaseSlot(ASYNCTIMER);
    TB0CTL &= ~(ID__8 + TBIE + MC_3); //TIMER_B_stop(TIMER_B0_BASE);
    TB0EX0 = TBIDEX_0;
    TBCCR0 = MAXIMUM_PERIOD;
    TB0CTL = TBCLR + ID__1 + TBSSEL_2;
    TB0CTL &= ~TBIFG; //TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
}

uint8_t ASYNCTIMER_handler()
{
    if (ASYNCTMR.ATCTL & AT_EN)
        enableTimer_B();
    else
        disableTimer_B();
    return 0x00;
}

