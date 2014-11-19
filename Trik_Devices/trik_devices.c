/*
 * trik_devices.c
 *
 *  Created on: 18 но€б. 2014 г.
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
    for (int j=0; j<MAX_DEVICES; j++) busy_table[j]=NNONE;
    for (int j=0; j<MAX_MOTORS; j++) MOT[j].MCTL=MOT[j].MDUT=MOT[j].MPER=MOT[j].MANG=MOT[j].MTMR=MOT[j].MVAL=MOT[j].MSTA=0;
    for (int j=0; j<MAX_MOTORS; j++) MOT[j].MOT_EN=MOT[j].MOT_PWR=MOT[j].MOT_DIR=MOT[j].MOT_DIR=0;
    for (int j=0; j<MAX_ENCODERS; j++) ENC[j].ECTL=ENC[j].EVAL=ENC[j].ESTA=0;
    for (int j=0; j<MAX_ENCODERS; j++) ENC[j].ENC_EN=ENC[j].ENC_PUP=ENC[j].ENC_TYP=0;
    ASYNCTMR.ATCTL=ASYNCTMR.ATVAL=0;
    ASYNCTMR.ATPER=MAX_DEVICES;
    for (int j=0; j<MAX_SENSORS; j++) SENS[j].SCTL=SENS[j].SIDX=SENS[j].SVAL=SENS[j].SSTA=0;
    for (int j=0; j<MAX_SENSORS; j++) SENS[j].SENS_EN=SENS[j].SENS_MOD=SENS[j].SENS_PUP=0;
}

//Init reference and temperature sensor for ADC
void initReferenceTemperature()
{
    //while(REF_isRefGenBusy(REF_BASE));
    //REF_setReferenceVoltage(REF_BASE,REF_VREF2_5V);
    //REF_enableReferenceVoltage(REF_BASE);
    REF_enableTempSensor(REF_BASE);
}

//Init ADC 10 bit
void initADC10()
{
    ADC10_A_init(ADC10_A_BASE,
                 ADC10_A_SAMPLEHOLDSOURCE_SC,
                 ADC10_A_CLOCKSOURCE_SMCLK,
                 ADC10_A_CLOCKDIVIDER_1);
    ADC10_A_enable(ADC10_A_BASE);
}

//Init B ports (PBEN)
void initPBPorts()
{
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN3);
}
