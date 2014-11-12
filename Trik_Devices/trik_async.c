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
    //Overflow interrupt frequency is 366,21093755 Hz
    TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
    /*
    TIMER_B_startContinuousMode(TIMER_B0_BASE,
            TIMER_B_CLOCKSOURCE_SMCLK,
            TIMER_B_CLOCKSOURCE_DIVIDER_1,
            TIMER_B_TBIE_INTERRUPT_ENABLE,
            TIMER_B_DO_CLEAR);
            */
    TIMER_B_startUpMode(TIMER_B0_BASE,
            TIMER_B_CLOCKSOURCE_SMCLK,
            TIMER_B_CLOCKSOURCE_DIVIDER_1,
            0x1000,
            TIMER_B_TBIE_INTERRUPT_ENABLE,
            TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE,
            TIMER_B_DO_CLEAR);

}

void disableTimer_B()
{
    TIMER_B_startContinuousMode(TIMER_B0_BASE,
            TIMER_B_CLOCKSOURCE_SMCLK,
            TIMER_B_CLOCKSOURCE_DIVIDER_1,
            TIMER_B_TBIE_INTERRUPT_DISABLE,
            TIMER_B_DO_CLEAR);
    TIMER_B_stop(TIMER_B0_BASE);
    TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
}

uint8_t ASYNCTIMER_hadler()
{
    if (ASYNCTMR.ATCTL & 0x0003)
    {
        enableTimer_B();
    }
    else
    {
        disableTimer_B();
    }
    return 0x00;
}

