/*
 * trik_touch.c
 *
 *  Created on: December 1, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_touch.h"
#include "driverlib.h"


//Return 1, if panel is touched
uint8_t isTouched()
{
    P5DIR &= ~(BIT0+BIT1);
    P5REN |= BIT1;
    P5OUT |= BIT1;
    P4DIR |= BIT6+BIT7;
    P4OUT &= ~(BIT6+BIT7);
    if (P5IN & BIT1)
        return NOT_TOUCHED;
    else
        return TOUCHED;
}
