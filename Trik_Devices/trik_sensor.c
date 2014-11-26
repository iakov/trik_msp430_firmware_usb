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

void SENSOR_enableController(uint8_t SENS_NUMBER)
{
    if ((busy_table[SENS_NUMBER]==NNONE) || (busy_table[SENS_NUMBER]==SENS_NUMBER))
    {
        busy_table[SENS_NUMBER]=SENS_NUMBER;
        SENS[SENS_NUMBER-SENSOR1].SENS_EN = ENABLE;
    }
}

void SENSOR_disableController(uint8_t SENS_NUMBER)
{
    busy_table[SENS_NUMBER]=NNONE;
    SENS[SENS_NUMBER-SENSOR1].SENS_EN = DISABLE;
}

uint32_t SENSOR_read_digital(uint8_t SENS_NUMBER)
{
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            P4OUT &= ~BIT5; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN5);
            P4DIR |= BIT5; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P6DIR &= ~BIT5; P6OUT |= BIT5; P6REN |= BIT5; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN5);
            }
            else
            {
                P6DIR &= ~BIT5; P6REN &= ~BIT5; P6OUT &= ~BIT5; //GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN5);
            }
            return (P6IN & BIT5); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN5);
        case SENSOR2:
            P4OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN4);
            P4DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P6DIR &= ~BIT4; P6OUT |= BIT4; P6REN |= BIT4; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN4);
            }
            else
            {
                P6DIR &= ~BIT4; P6REN &= ~BIT4; P6OUT &= ~BIT4; //GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN4);
            }
            return (P6IN & BIT4); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN4);
        case SENSOR3:
            P4OUT &= ~BIT3; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN3);
            P4DIR |= BIT3; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P6DIR &= ~BIT3; P6OUT |= BIT3; P6REN |= BIT3; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN3);
            }
            else
            {
                P6DIR &= ~BIT3; P6REN &= ~BIT3; P6OUT &= ~BIT3; //GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN3);
            }
            return (P6IN & BIT3); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN3);
        case SENSOR4:
            P4OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
            P4DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P6DIR &= ~BIT2; P6OUT |= BIT2; P6REN |= BIT2; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN2);
            }
            else
            {
                P6DIR &= ~BIT2; P6REN &= ~BIT2; P6OUT &= ~BIT2; //GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN2);
            }
            return (P6IN & BIT2); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2);
        case SENSOR5:
            P3OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            P3DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P6DIR &= ~BIT1; P6OUT |= BIT1; P6REN |= BIT1; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN1);
            }
            else
            {
                P6DIR &= ~BIT1; P6REN &= ~BIT1; P6OUT &= ~BIT1; //GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN1);
            }
            return (P6IN & BIT1); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1);
        case SENSOR6:
            P3OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            P3DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P6DIR &= ~BIT0; P6OUT |= BIT0; P6REN |= BIT0; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN0);
            }
            else
            {
                P6DIR &= ~BIT0; P6REN &= ~BIT0; P6OUT &= ~BIT0; //GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN0);
            }
            return (P6IN & BIT0); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0);
        case SENSOR7:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P2DIR &= ~BIT0; P2OUT |= BIT0; P2REN |= BIT0; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN0);
            }
            else
            {
                P2DIR &= ~BIT0; P2REN &= ~BIT0; P2OUT &= ~BIT0; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0);
            }
            return (P2IN & BIT0); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN0);
        case SENSOR8:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P2DIR &= ~BIT3; P2OUT |= BIT3; P2REN |= BIT3; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN3);
            }
            else
            {
                P2DIR &= ~BIT3; P2REN &= ~BIT3; P2OUT &= ~BIT3; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN3);
            }
            return (P2IN & BIT3); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3);
        case SENSOR9:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P2DIR &= ~BIT4; P2OUT |= BIT4; P2REN |= BIT4; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN4);
            }
            else
            {
                P2DIR &= ~BIT4; P2REN &= ~BIT4; P2OUT &= ~BIT4; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
            }
            return (P2IN & BIT4); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN4);
        case SENSOR10:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P1DIR &= ~BIT0; P1OUT |= BIT0; P1REN |= BIT0; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN0);
            }
            else
            {
                P1DIR &= ~BIT0; P1REN &= ~BIT0; P1OUT &= ~BIT0; //GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
            }
            return (P1IN & BIT0); //return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN0);
        case SENSOR11:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P2DIR &= ~BIT5; P2OUT |= BIT5; P2REN |= BIT5; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN5);
            }
            else
            {
                P2DIR &= ~BIT5; P2REN &= ~BIT5; P2OUT &= ~BIT5; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN5);
            }
            return (P2IN & BIT5); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5);
        case SENSOR12:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P2DIR &= ~BIT2; P2OUT |= BIT2; P2REN |= BIT2; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN2);
            }
            else
            {
                P2DIR &= ~BIT2; P2REN &= ~BIT2; P2OUT &= ~BIT2; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2);
            }
            return (P2IN & BIT2); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN2);
        case SENSOR13:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P2DIR &= ~BIT1; P2OUT |= BIT1; P2REN |= BIT1; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN1);
            }
            else
            {
                P2DIR &= ~BIT1; P2REN &= ~BIT1; P2OUT &= ~BIT1; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
            }
            return (P2IN & BIT1); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1);
        case SENSOR14:
            if (SENS[SENS_NUMBER-SENSOR1].SENS_PUP==PULL_UP)
            {
                P1DIR &= ~BIT6; P1OUT |= BIT6; P1REN |= BIT6; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN6);
            }
            else
            {
                P1DIR &= ~BIT6; P1REN &= ~BIT6; P1OUT &= ~BIT6; //GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
            }
            return (P1IN & BIT6); //return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6);
        default:
            return 0x00;
    }
}

uint32_t SENSOR_read_analog(uint8_t SENS_NUMBER)
{
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            P4OUT &= ~BIT5; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN5);
            P4DIR |= BIT5; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
            P6SEL |= BIT5; P6DIR &= ~BIT5; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN5);
            /*
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A5,
                    ADC10_A_VREFPOS_AVCC,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
            */
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH0 + ADC10INCH2;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY);
            return ADC10MEM0;
        case SENSOR2:
            P4OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN4);
            P4DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
            P6SEL |= BIT4; P6DIR &= ~BIT4; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN4);
            /*
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A4,
                    ADC10_A_VREFPOS_AVCC,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
            */
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH2;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY);
            return ADC10MEM0;
        case SENSOR3:
            P4OUT &= ~BIT3; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN3);
            P4DIR |= BIT3; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
            P6SEL |= BIT3; P6DIR &= ~BIT3; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN3);
            /*
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A3,
                    ADC10_A_VREFPOS_AVCC,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
            */
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH0 + ADC10INCH1;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY);
            return ADC10MEM0;
        case SENSOR4:
            P4OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
            P4DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
            P6SEL |= BIT2; P6DIR &= ~BIT2; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN2);
            /*
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A2,
                    ADC10_A_VREFPOS_AVCC,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
            */
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH1;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY);
            return ADC10MEM0;
        case SENSOR5:
            P3OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            P3DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
            P6SEL |= BIT1; P6DIR &= ~BIT1; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN1);
            /*
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A1,
                    ADC10_A_VREFPOS_AVCC,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
            */
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH0;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY);
            return ADC10MEM0;
        case SENSOR6:
            P3OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            P3DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);
            P6SEL |= BIT0; P6DIR &= ~BIT0; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN0);
            /*
            ADC10_A_memoryConfigure(ADC10_A_BASE,
                    ADC10_A_INPUT_A0,
                    ADC10_A_VREFPOS_AVCC,
                    ADC10_A_VREFNEG_AVSS);
            ADC10_A_startConversion(ADC10_A_BASE,
                    ADC10_A_SINGLECHANNEL);
            while(ADC10_A_isBusy(ADC10_A_BASE));
            return ADC10_A_getResults(ADC10_A_BASE);
            */
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = 0x00;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY);
            return ADC10MEM0;
        case SENSOR7:
            if (P2IN & BIT0) //if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN0))
                return UINT32_MAX;
            else
                return 0x00000000;
        case SENSOR8:
            if (P2IN & BIT3) //if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3))
                return UINT32_MAX;
            else
                return 0x00000000;
        case SENSOR9:
            if (P2IN & BIT4) //if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN4))
                return UINT32_MAX;
            else
                return 0x00000000;
        case SENSOR10:
            if (P1IN & BIT0) //if (GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN0))
                return UINT32_MAX;
            else
                return 0x00000000;
        case SENSOR11:
            if (P2IN & BIT5) //if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5))
                return UINT32_MAX;
            else
                return 0x00000000;
        case SENSOR12:
            if (P2IN & BIT2) //if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN2))
                return UINT32_MAX;
            else
                return 0x00000000;
        case SENSOR13:
            if (P2IN & BIT1) //if (GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1))
                return UINT32_MAX;
            else
                return 0x00000000;
        case SENSOR14:
            if (P1IN & BIT6) //if (GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6))
                return UINT32_MAX;
            else
                return 0x00000000;
        default:
            return 0x00;
    }
}

uint32_t SENSOR_read_temperature(uint8_t SENS_NUMBER)
{
    /*
    ADC10_A_memoryConfigure(ADC10_A_BASE,
            ADC10_A_INPUT_TEMPSENSOR,
            ADC10_A_VREFPOS_AVCC,
            ADC10_A_VREFNEG_AVSS);
    ADC10_A_startConversion(ADC10_A_BASE,
            ADC10_A_SINGLECHANNEL);
    while(ADC10_A_isBusy(ADC10_A_BASE));
    return ADC10_A_getResults(ADC10_A_BASE);
    */
    ADC10CTL0 &= ~ADC10ENC;
    ADC10MCTL0 = ADC10INCH1 + ADC10INCH3;
    ADC10CTL0 |= ADC10SC + ADC10ENC;
    while (ADC10CTL1 & ADC10BUSY);
    return ADC10MEM0;
}

uint32_t SENSOR_read_voltage(uint8_t SENS_NUMBER)
{
    P6SEL |= BIT6; P6DIR &= ~BIT6; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN6);
    /*
    ADC10_A_memoryConfigure(ADC10_A_BASE,
            ADC10_A_INPUT_A6,
            ADC10_A_VREFPOS_AVCC,
            ADC10_A_VREFNEG_AVSS);
    ADC10_A_startConversion(ADC10_A_BASE,
            ADC10_A_SINGLECHANNEL);
    while(ADC10_A_isBusy(ADC10_A_BASE));
    return ADC10_A_getResults(ADC10_A_BASE);
    */
    ADC10CTL0 &= ~ADC10ENC;
    ADC10MCTL0 = ADC10INCH1 + ADC10INCH2;
    ADC10CTL0 |= ADC10SC + ADC10ENC;
    while (ADC10CTL1 & ADC10BUSY);
    return ADC10MEM0;
}

uint32_t SENSOR_read_current(uint8_t SENS_NUMBER)
{
    P6SEL |= BIT7; P6DIR &= ~BIT7; //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN7);
    /*
    ADC10_A_memoryConfigure(ADC10_A_BASE,
            ADC10_A_INPUT_A7,
            ADC10_A_VREFPOS_AVCC,
            ADC10_A_VREFNEG_AVSS);
    ADC10_A_startConversion(ADC10_A_BASE,
            ADC10_A_SINGLECHANNEL);
    while(ADC10_A_isBusy(ADC10_A_BASE));
    return ADC10_A_getResults(ADC10_A_BASE);
    */
    ADC10CTL0 &= ~ADC10ENC;
    ADC10MCTL0 = ADC10INCH0 + ADC10INCH1 + ADC10INCH2;
    ADC10CTL0 |= ADC10SC + ADC10ENC;
    while (ADC10CTL1 & ADC10BUSY);
    return ADC10MEM0;
}

void SENSOR_hadler(uint8_t SENS_NUMBER)
{
    //Async/single read mode
    if (SENS[SENS_NUMBER-SENSOR1].SCTL & 0x4000)
        SENS[SENS_NUMBER-SENSOR1].SENS_MOD = ENABLE;
    else
        SENS[SENS_NUMBER-SENSOR1].SENS_MOD = DISABLE;
    //Enable/disable and read
    if (SENS[SENS_NUMBER-SENSOR1].SCTL & 0x8000)
    {
        //Sensor enable
        SENSOR_enableController(SENS_NUMBER);
        //Enable reading sensor data
        if (SENS[SENS_NUMBER-SENSOR1].SCTL & 0x0001)
        {
            if (SENS[SENS_NUMBER-SENSOR1].SIDX==DIGITAL_INP) SENS[SENS_NUMBER-SENSOR1].SVAL=SENSOR_read_digital(SENS_NUMBER);
            if (SENS[SENS_NUMBER-SENSOR1].SIDX==ANALOG_INP) SENS[SENS_NUMBER-SENSOR1].SVAL=SENSOR_read_analog(SENS_NUMBER);
            if (SENS[SENS_NUMBER-SENSOR1].SIDX==MCU_TEMP) SENS[SENS_NUMBER-SENSOR1].SVAL=SENSOR_read_temperature(SENS_NUMBER);
            if (SENS[SENS_NUMBER-SENSOR1].SIDX==MOTOR_VOLTAGE) SENS[SENS_NUMBER-SENSOR1].SVAL=SENSOR_read_voltage(SENS_NUMBER);
            if (SENS[SENS_NUMBER-SENSOR1].SIDX==MOTOR_CURRENT) SENS[SENS_NUMBER-SENSOR1].SVAL=SENSOR_read_current(SENS_NUMBER);
        }
    }
    else
        SENSOR_disableController(SENS_NUMBER);

    SENS[SENS_NUMBER-SENSOR1].SSTA = SENS_NO_ERROR;
}
