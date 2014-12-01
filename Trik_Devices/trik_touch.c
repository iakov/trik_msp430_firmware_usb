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
    /*
    P5REN &= ~(BIT0+BIT1);
    P5OUT &= ~(BIT0+BIT1);
    P5DIR &= ~(BIT0+BIT1);
    P5SEL |= BIT0;
    P4DIR |= BIT6+BIT7;
    P4OUT &= ~BIT6;
    P4OUT |= BIT7;
*/


    P5SEL &= ~(BIT0+BIT1);
    P5OUT &= ~(BIT0+BIT1);
    P5DIR &= ~(BIT0+BIT1);
    P5REN |= BIT1;
    P5OUT |= BIT1;
    P4OUT &= ~(BIT6+BIT7);
    P4REN &= ~(BIT6+BIT7);
    P4SEL &= ~(BIT6+BIT7);
    P4DIR |= BIT6+BIT7;

    /*
    if (P5IN & BIT1)
        return NOT_TOUCHED;
    else
        return TOUCHED;
        */
while (P5IN & BIT1) ;
        return P5IN;
}

//Return X coordinate of touch
uint16_t touchReadX()
{
    P5REN &= ~(BIT0+BIT1);
    P5OUT &= ~(BIT0+BIT1);
    P5DIR &= ~(BIT0+BIT1);
    P5SEL |= BIT0;
    P4DIR |= BIT6+BIT7;
    P4OUT &= ~BIT6;
    P4OUT |= BIT7;
    ADC10CTL0 &= ~ADC10ENC;
    ADC10MCTL0 = ADC10INCH_8;
    ADC10CTL0 |= ADC10SC + ADC10ENC;
    while (ADC10CTL1 & ADC10BUSY)
        ;
    return ADC10MEM0;
}

//Return X coordinate of touch
uint16_t touchReadY()
{
    P5REN &= ~(BIT0+BIT1);
    P5OUT &= ~(BIT0+BIT1);
    P5DIR &= ~(BIT0+BIT1);
    P5SEL |= BIT0;
    P4DIR |= BIT6+BIT7;
    P4OUT &= ~BIT7;
    P4OUT |= BIT6;
    ADC10CTL0 &= ~ADC10ENC;
    ADC10MCTL0 = ADC10INCH_9;
    ADC10CTL0 |= ADC10SC + ADC10ENC;
    while (ADC10CTL1 & ADC10BUSY)
        ;
    return ADC10MEM0;
}
