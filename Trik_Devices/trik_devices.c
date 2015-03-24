/*
 * trik_devices.c
 *
 *  Created on: November 18, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_motor.h"
#include "trik_encoder.h"
#include "trik_async.h"
#include "trik_sensor.h"
#include "trik_touch.h"
#include "trik_pwm.h"
#include "trik_softpwm.h"
#include "trik_softi2c.h"

//Reset touch parameters
void resetTouch()
{
    TOUCH.MINX = UINT16_MAX;
    TOUCH.MAXX = 0;
    TOUCH.MINY = UINT16_MAX;
    TOUCH.MAXY = 0;
    TOUCH.CURX = 0;
    TOUCH.CURY = 0;
}

//Init variables, arrays and structures
void initGlobalVars()
{
    for (int j=0; j<MAX_DEVICES; j++)
        busy_table[j] = NNONE;

    for (int j=0; j<MAX_MOTORS; j++)
        MOT[j].MCTL = MOT[j].MDUT = MOT[j].MPER = MOT[j].MANG = MOT[j].MTMR = MOT[j].MVAL = MOT[j].MSTA = MOT[j].MERR = 0x0000;

    for (int j=0; j<MAX_ENCODERS; j++)
        ENC[j].ECTL = ENC[j].EVAL = ENC[j].ESTA = 0x0000;

    for (int j=0; j<MAX_SENSORS; j++)
        SENS[j].SCTL = SENS[j].SIDX = SENS[j].SVAL = SENS[j].SSTA = 0x0000;

    ASYNCTMR.ATCTL = ASYNCTMR.ATVAL = 0;
    ASYNCTMR.ATPER = MAX_DEVICES;

    TOUCH.TMOD = CAL_OFF;
    TOUCH.SCRX = 320;
    TOUCH.SCRY = 240;
    resetTouch();
    mouseReport.lx = mouseReport.ly = mouseReport.hx = mouseReport.hy = mouseReport.buttons = 0;

    for (int j=0; j<MAX_PWMS; j++)
        PWM[j].PCTL = PWM[j].PDUT = PWM[j].PPER = PWM[j].PSTA = 0x0000;

    for (int j=0; j<MAX_SPWMS; j++)
        SPWM[j].SPCTL = SPWM[j].SPDUT = SPWM[j].SPPER = SPWM[j].SPSTA = SPWM[j].SPCNT = 0x0000;

    Idelay = 200;
    for (int j=0; j<MAX_I2CS; j++)
        I2C[j].ICTL = I2C[j].IDAT = I2C[j].IDEV = I2C[j].IERR = I2C[j].IREG = I2C[j].ISTA = I2C[j].IIDX = I2C[j].IVAL = 0x00;

}

//Init reference and temperature sensor for ADC
void initReferenceTemperature()
{
    while(REFCTL0 & REFGENBUSY)
        ;
    REFCTL0 |= REFMSTR + REFON;
}

//Init ADC 10 bit
void initADC10()
{
    ADC10CTL0 = ADC10SHT1 + ADC10ON;
    ADC10CTL1 = ADC10SHP + ADC10DIV0 + ADC10DIV1 + ADC10DIV2 + ADC10SSEL0 + ADC10SSEL1;
    ADC10CTL2 = ADC10RES;

}

//Init B ports (PBEN)
void initPBPorts()
{
    P5DIR |= BIT3; //GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN3);
    P5OUT |= BIT3; //GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN3);
}

//Init PWM for motors
void initPWM()
{
    TA0CCTL1 = OUTMOD_7;                            // CCR1 reset/set
    TA0CCTL2 = OUTMOD_7;                            // CCR2 reset/set
    TA0CCTL3 = OUTMOD_7;                            // CCR3 reset/set
    TA0CCTL4 = OUTMOD_7;                            // CCR4 reset/set
    TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;        // SMCLK, up mode, clear TAR, divider - 8
}

//Test, if slot busy by other device
uint8_t isSlotBusy(uint8_t DEV_NUMBER)
{
    if ((busy_table[DEV_NUMBER]==NNONE) || (busy_table[DEV_NUMBER]==DEV_NUMBER))
        return SLOT_FREE;
    else
        return SLOT_BUSY;
}

//Make slot busy
void reseveSlot(uint8_t DEV_NUMBER)
{
    busy_table[DEV_NUMBER] = DEV_NUMBER;
}

//Make slot free
void releaseSlot(uint8_t DEV_NUMBER)
{
    busy_table[DEV_NUMBER] = NNONE;
}
