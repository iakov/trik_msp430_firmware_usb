/*
 * trik_sensor.c
 *
 *  Created on: October 31, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_devices.h"
#include "trik_sensor.h"
#include "driverlib.h"






//Handler
uint8_t SENSOR_hadler(uint8_t SENS_NUMBER)
{
    if (SENS[SENS_NUMBER-SENSOR1].SCTL & 0x8000)
    {
        //Enable/disable
        if (!(SENS[SENS_NUMBER-SENSOR1].SENS_EN)) SENSOR_enableController(SENS_NUMBER);


        return 0x00;
    }
    else
    {
        if (SENS[SENS_NUMBER-SENSOR1].SENS_EN) SENSOR_disableController(SENS_NUMBER);
        return 0x00;
    }
}
