/*
 * trik_async.c
 *
 *  Created on: November 11, 2014
 *      Author: Rostislav Varzar
 */

//Init timer B for asynchronous packets
void initTimer_B()
{
    TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
    TIMER_B_startContinuousMode(TIMER_B0_BASE,
            TIMER_B_CLOCKSOURCE_SMCLK,
            TIMER_B_CLOCKSOURCE_DIVIDER_1,
            TIMER_B_TBIE_INTERRUPT_ENABLE,
            TIMER_B_DO_CLEAR);
}

