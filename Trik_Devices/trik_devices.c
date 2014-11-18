/*
 * trik_devices.c
 *
 *  Created on: 18 но€б. 2014 г.
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
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
void initReference()
{
}
}
