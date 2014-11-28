/*
 * trik_devices.c
 *
 *  Created on: November 18, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "driverlib.h"
#include "trik_devices.h"
#include "Trik_Devices/trik_motor.h"
#include "Trik_Devices/trik_encoder.h"
#include "Trik_Devices/trik_async.h"
#include "Trik_Devices/trik_sensor.h"

//Init variables, arrays and structures
void initGlobalVars()
{
    for (int j=0; j<MAX_DEVICES; j++)
        busy_table[j] = NNONE;

    for (int j=0; j<MAX_MOTORS; j++)
        MOT[j].MCTL = MOT[j].MDUT = MOT[j].MPER = MOT[j].MANG = MOT[j].MTMR = MOT[j].MVAL = MOT[j].MSTA = 0x0000;

    for (int j=0; j<MAX_ENCODERS; j++)
        ENC[j].ECTL = ENC[j].EVAL = ENC[j].ESTA = 0x0000;

    for (int j=0; j<MAX_SENSORS; j++)
        SENS[j].SCTL = SENS[j].SIDX = SENS[j].SVAL = SENS[j].SSTA = 0x0000;

    ASYNCTMR.ATCTL = ASYNCTMR.ATVAL = 0;
    ASYNCTMR.ATPER = MAX_DEVICES;
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
