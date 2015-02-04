/*
 * trik_touch.c
 *
 *  Created on: December 1, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_touch.h"

//Return 1, if panel is touched
uint8_t isTouched()
{
    P4DIR |= BIT6+BIT7;
    P4OUT &= ~(BIT6+BIT7);
    P5DIR &= ~(BIT0+BIT1);
    P5OUT &= ~(BIT0+BIT1);
    P5SEL &= ~(BIT0+BIT1);
    P5REN &= ~(BIT0+BIT1);
    //Problem with recharging touch panel or setting pull up
    for (int d=0;d<50;d++)
    {
        P5OUT |= BIT1;
        P5REN |= BIT1;
    }
    if (P5IN & BIT1)
        return NOT_TOUCHED;
    else
        return TOUCHED;
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
    P5SEL |= BIT1;

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
