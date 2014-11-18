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
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN5);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN5);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN5);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN5);
        case SENSOR2:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN4);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN4);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN4);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN4);
        case SENSOR3:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN3);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN3);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN3);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN3);
        case SENSOR4:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN2);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN2);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2);
        case SENSOR5:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN1);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN1);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1);
        case SENSOR6:
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN0);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN0);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0);
        case SENSOR7:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN0);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN0);
        case SENSOR8:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN3);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN3);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3);
        case SENSOR9:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN4);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN4);
        case SENSOR10:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN0);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN0);
        case SENSOR11:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN5);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN5);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5);
        case SENSOR12:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN2);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN2);
        case SENSOR13:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN1);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1);
        case SENSOR14:
            switch (SENS[SENS_NUMBER-SENSOR1].SENS_PUP)
            {
                case PULL_OFF:
                    GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
                    break;
                case PULL_UP:
                    GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN6);
                    break;
                default:;
            }
            return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6);
        default: return 0x00;
    }
}

uint32_t SENSOR_read_analog(uint8_t SENS_NUMBER)
{
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A5,
                    ADC10_A_VREFPOS_INT,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
        case SENSOR2:
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A4,
                    ADC10_A_VREFPOS_INT,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
        case SENSOR3:
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A3,
                    ADC10_A_VREFPOS_INT,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
        case SENSOR4:
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A2,
                    ADC10_A_VREFPOS_INT,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
        case SENSOR5:
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A1,
                    ADC10_A_VREFPOS_INT,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
        case SENSOR6:
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A0,
                    ADC10_A_VREFPOS_INT,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
        case SENSOR7:
            if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN0))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        case SENSOR8:
            if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        case SENSOR9:
            if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN4))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        case SENSOR10:
            if (GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN0))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        case SENSOR11:
            if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        case SENSOR12:
            if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN2))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        case SENSOR13:
            if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        case SENSOR14:
            if (GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6))
                return 0xFFFFFFFF;
            else
                return 0x00000000;
        default: return 0x00;
    }
}

/*
void SENSOR_enableDigitalMode(uint8_t SENS_NUMBER)
{
    SENS[SENS_NUMBER-SENSOR1].SENS_MOD = DIGITAL_INP;
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN5);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P6,GPIO_PIN5);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN5);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
            break;
        case SENSOR2:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN4);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P6,GPIO_PIN4);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN4);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
            break;
        case SENSOR3:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN3);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P6,GPIO_PIN3);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN3);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN3);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
            break;
        case SENSOR4:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN2);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P6,GPIO_PIN2);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
            break;
        case SENSOR5:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN1);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P6,GPIO_PIN1);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
            break;
        case SENSOR6:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN0);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P6,GPIO_PIN0);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case SENSOR7:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P2,GPIO_PIN0);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN0);
            break;
        case SENSOR8:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN3);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P2,GPIO_PIN3);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN3);
            break;
        case SENSOR9:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P2,GPIO_PIN4);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN4);
            break;
        case SENSOR10:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P1,GPIO_PIN0);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN0);
            break;
        case SENSOR11:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN5);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P2,GPIO_PIN5);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN5);
            break;
        case SENSOR12:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P2,GPIO_PIN2);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN2);
            break;
        case SENSOR13:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P2,GPIO_PIN1);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN1);
            break;
        case SENSOR14:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_OFF) GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_DN)  GPIO_setAsInputPinWithPullDownresistor(GPIO_PORT_P1,GPIO_PIN6);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)  GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN6);
            break;
        default:;
    }
}
*/

/*
void SENSOR_enableAnalogMode(uint8_t SENS_NUMBER)
{
    SENS[SENS_NUMBER-SENSOR1].SENS_MOD = ANALOG_INP;
    while(REF_isRefGenBusy(REF_BASE));
    REF_setReferenceVoltage(REF_BASE,REF_VREF2_5V);
    REF_enableReferenceVoltage(REF_BASE);
    REF_enableTempSensor(REF_BASE);
    ADC10_A_init(ADC10_A_BASE,
                 ADC10_A_SAMPLEHOLDSOURCE_SC,
                 ADC10_A_CLOCKSOURCE_SMCLK,
                 ADC10_A_CLOCKDIVIDER_1);
    ADC10_A_enable(ADC10_A_BASE);
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN5);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
            break;
        case SENSOR2:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN4);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
            break;
        case SENSOR3:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN3);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN3);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
            break;
        case SENSOR4:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
            GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
            break;
        case SENSOR5:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
            break;
        case SENSOR6:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);
            break;
        case SENSOR7:
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0);
            break;
        case SENSOR8:
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN3);
            break;
        case SENSOR9:
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
            break;
        case SENSOR10:
            GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
            break;
        case SENSOR11:
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN5);
            break;
        case SENSOR12:
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2);
            break;
        case SENSOR13:
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
            break;
        case SENSOR14:
            GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
            break;
        default:;
    }
}
*/

//Handler
uint8_t SENSOR_hadler(uint8_t SENS_NUMBER)
{
    if (SENS[SENS_NUMBER-SENSOR1].SCTL & 0x8000)
    {
        //Enable/disable
        if (!(SENS[SENS_NUMBER-SENSOR1].SENS_EN)) SENSOR_enableController(SENS_NUMBER);

        //Async/single read mode
        if (SENS[SENS_NUMBER-SENSOR1].SCTL & 0x4000)
        {
            SENS[SENS_NUMBER-SENSOR1].SENS_MOD = ENABLE;
        }
        else
        {
            SENS[SENS_NUMBER-SENSOR1].SENS_MOD = DISABLE;
        }

        //Enable reading sensor data
        if (SENS[SENS_NUMBER-SENSOR1].SCTL & 0x0001)
        {
            if (SENS[SENS_NUMBER-SENSOR1].SIDX==DIGITAL_INP) SENS[SENS_NUMBER-SENSOR1].SVAL=SENSOR_read_digital(SENS_NUMBER);
            if (SENS[SENS_NUMBER-SENSOR1].SIDX==ANALOG_INP)  SENS[SENS_NUMBER-SENSOR1].SVAL=SENSOR_read_analog(SENS_NUMBER);
        }

        return 0x00;
    }
    else
    {
        if (SENS[SENS_NUMBER-SENSOR1].SENS_EN) SENSOR_disableController(SENS_NUMBER);
        return 0x00;
    }
}
