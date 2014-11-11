/*
 * trik_async.c
 *
 *  Created on: November 11, 2014
 *      Author: Rostislav Varzar
 */

#include "driverlib.h"

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

// Timer_B7 Interrupt Vector (TBIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERB1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMERB1_VECTOR)))
#endif
void TIMERB1_ISR(void)
{
    /* Any access, read or write, of the TBIV register automatically resets the
       highest "pending" interrupt flag. */
    switch(__even_in_range(TBIV,14))
    {
    case  0: break;                          // No interrupt
    case  2: break;                          // CCR1 not used
    case  4: break;                          // CCR2 not used
    case  6: break;                          // CCR3 not used
    case  8: break;                          // CCR4 not used
    case 10: break;                          // CCR5 not used
    case 12: break;                          // CCR6 not used
    case 14:                                                 // overflow

        /*
        //sprintf(newString,"Oh, my timer!\r\n");
        sprintf(newString,"CNT1=%d\r\n",ENC[ENCODER1-ENCODER1].EVAL);
        if (cdcSendDataInBackground((uint8_t*)newString,
                strlen(newString),CDC0_INTFNUM,1))
        {  // Send message to other App
            SendError = 0x01;                          // Something went wrong -- exit
        }
        */

        break;
    default: break;
    }
    TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
}

