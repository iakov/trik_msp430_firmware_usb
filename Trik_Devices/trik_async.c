/*
 * trik_async.c
 *
 *  Created on: November 11, 2014
 *      Author: Rostislav Varzar
 */

#include "driverlib.h"
#include "trik_async.h"

//Init timer B for asynchronous packets
void enableTimer_B()
{
    //Overflow interrupt frequency is 10 kHz
    TB0CTL &= ~TBIFG; //TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
    /*
    TIMER_B_startUpMode(TIMER_B0_BASE,
            TIMER_B_CLOCKSOURCE_SMCLK,
            TIMER_B_CLOCKSOURCE_DIVIDER_1,
            0x0960,
            TIMER_B_TBIE_INTERRUPT_ENABLE,
            TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE,
            TIMER_B_DO_CLEAR);
    */
    TB0CTL &= ~ID__8;
    TB0EX0 = TBIDEX_0;
    TBCCR0 = 0x0960;
    TB0CTL = MC_1 + TBCLR + ID__1 + TBIE + TBSSEL_2;
}

void disableTimer_B()
{
    /*
    TIMER_B_startUpMode(TIMER_B0_BASE,
            TIMER_B_CLOCKSOURCE_SMCLK,
            TIMER_B_CLOCKSOURCE_DIVIDER_1,
            0xFFFF,
            TIMER_B_TBIE_INTERRUPT_DISABLE,
            TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE,
            TIMER_B_DO_CLEAR);
    */
    TB0CTL &= ~(ID__8 + TBIE + MC_3); //TIMER_B_stop(TIMER_B0_BASE);
    TB0EX0 = TBIDEX_0;
    TBCCR0 = 0xFFFF;
    TB0CTL = TBCLR + ID__1 + TBSSEL_2;
    TB0CTL &= ~TBIFG; //TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
}

uint8_t ASYNCTIMER_hadler()
{
    if (ASYNCTMR.ATCTL & 0x0003)
        enableTimer_B();
    else
        disableTimer_B();
    return 0x00;
}

