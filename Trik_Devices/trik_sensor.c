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

//API functions
void SENSOR_enableController(uint8_t SENS_NUMBER)
{
    if (busy_table[SENS_NUMBER]==NNONE)
    {
        busy_table[SENS_NUMBER]=SENS_NUMBER;
        SENS[SENS_NUMBER-SENSOR1].SENS_EN = ENABLE;
        switch (SENS_NUMBER)
        {
            case SENSOR1:

                break;
            default:;
        }
    }
}

void SENSOR_disableController(uint8_t SENS_NUMBER)
{
    busy_table[SENS_NUMBER]=NNONE;
    SENS[SENS_NUMBER-SENSOR1].SENS_EN = DISABLE;
    switch (SENS_NUMBER)
    {
        case SENSOR1:

            break;
        default:;
    }
}

uint32_t SENSOR_read_digital(uint8_t SENS_NUMBER)
{
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN5);
        case SENSOR2:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN4);
        case SENSOR3:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN3);
        case SENSOR4:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2);
        case SENSOR5:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1);
        case SENSOR6:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0);
        case SENSOR7:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN0);
        case SENSOR8:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3);
        case SENSOR9:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN4);
        case SENSOR10:
            return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN0);
        case SENSOR11:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5);
        case SENSOR12:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN2);
        case SENSOR13:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1);
        case SENSOR14:
            return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6);
        default: return 0x00;
    }
}

uint32_t SENSOR_read_analog(uint8_t SENS_NUMBER)
{
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN5);
        case SENSOR2:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN4);
        case SENSOR3:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN3);
        case SENSOR4:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2);
        case SENSOR5:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1);
        case SENSOR6:
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0);
        case SENSOR7:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN0);
        case SENSOR8:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3);
        case SENSOR9:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN4);
        case SENSOR10:
            return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN0);
        case SENSOR11:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5);
        case SENSOR12:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN2);
        case SENSOR13:
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1);
        case SENSOR14:
            return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6);
        default: return 0x00;
    }
}




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
