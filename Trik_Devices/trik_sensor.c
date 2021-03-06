/*
 * trik_sensor.c
 *
 *  Created on: October 31, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_sensor.h"

// Sensor enable
void SENSOR_enableController(uint8_t SENS_NUMBER)
{
}

// Sensor disable
void SENSOR_disableController(uint8_t SENS_NUMBER)
{
}

// Read digital value of sensor
uint32_t SENSOR_read_digital(uint8_t SENS_NUMBER)
{
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            P4OUT &= ~BIT5; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN5);
            P4DIR |= BIT5; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
            P6SEL &= ~BIT5;
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN5);*/
                P6DIR &= ~BIT5;
                P6OUT |= BIT5;
                P6REN |= BIT5;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN5);*/
                P6DIR &= ~BIT5;
                P6REN &= ~BIT5;
                P6OUT &= ~BIT5;
            }
            return (P6IN & BIT5); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN5);
        case SENSOR2:
            P4OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN4);
            P4DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
            P6SEL &= ~BIT4;
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN4);*/
                P6DIR &= ~BIT4;
                P6OUT |= BIT4;
                P6REN |= BIT4;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN4);*/
                P6DIR &= ~BIT4;
                P6REN &= ~BIT4;
                P6OUT &= ~BIT4;
            }
            return (P6IN & BIT4); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN4);
        case SENSOR3:
            P4OUT &= ~BIT3; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN3);
            P4DIR |= BIT3; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
            P6SEL &= ~BIT3;
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN3);*/
                P6DIR &= ~BIT3;
                P6OUT |= BIT3;
                P6REN |= BIT3;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN3);*/
                P6DIR &= ~BIT3;
                P6REN &= ~BIT3;
                P6OUT &= ~BIT3;
            }
            return (P6IN & BIT3); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN3);
        case SENSOR4:
            P4OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
            P4DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
            P6SEL &= ~BIT2;
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN2);*/
                P6DIR &= ~BIT2;
                P6OUT |= BIT2;
                P6REN |= BIT2;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN2);*/
                P6DIR &= ~BIT2;
                P6REN &= ~BIT2;
                P6OUT &= ~BIT2;
            }
            return (P6IN & BIT2); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2);
        case SENSOR5:
            P3OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            P3DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
            P6SEL &= ~BIT1;
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN1);*/
                P6DIR &= ~BIT1;
                P6OUT |= BIT1;
                P6REN |= BIT1;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN1);*/
                P6DIR &= ~BIT1;
                P6REN &= ~BIT1;
                P6OUT &= ~BIT1;
            }
            return (P6IN & BIT1); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1);
        case SENSOR6:
            P3OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            P3DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);
            P6SEL &= ~BIT0;
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P6,GPIO_PIN0);*/
                P6DIR &= ~BIT0;
                P6OUT |= BIT0;
                P6REN |= BIT0;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN0);*/
                P6DIR &= ~BIT0;
                P6REN &= ~BIT0;
                P6OUT &= ~BIT0;
            }
            return (P6IN & BIT0); //return GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0);
        case SENSOR7:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN0);*/
                P2DIR &= ~BIT0;
                P2OUT |= BIT0;
                P2REN |= BIT0;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0);*/
                P2DIR &= ~BIT0;
                P2REN &= ~BIT0;
                P2OUT &= ~BIT0;
            }
            return (P2IN & BIT0); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN0);
        case SENSOR8:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN3);*/
                P2DIR &= ~BIT3;
                P2OUT |= BIT3;
                P2REN |= BIT3;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN3);*/
                P2DIR &= ~BIT3;
                P2REN &= ~BIT3;
                P2OUT &= ~BIT3;
            }
            return (P2IN & BIT3); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3);
        case SENSOR9:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN4);*/
                P2DIR &= ~BIT4;
                P2OUT |= BIT4;
                P2REN |= BIT4;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);*/
                P2DIR &= ~BIT4;
                P2REN &= ~BIT4;
                P2OUT &= ~BIT4;
            }
            return (P2IN & BIT4); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN4);
        case SENSOR10:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN0);*/
                P1DIR &= ~BIT0;
                P1OUT |= BIT0;
                P1REN |= BIT0;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);*/
                P1DIR &= ~BIT0;
                P1REN &= ~BIT0;
                P1OUT &= ~BIT0;
            }
            return (P1IN & BIT0); //return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN0);
        case SENSOR11:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN5);*/
                P2DIR &= ~BIT5;
                P2OUT |= BIT5;
                P2REN |= BIT5;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN5);*/
                P2DIR &= ~BIT5;
                P2REN &= ~BIT5;
                P2OUT &= ~BIT5;
            }
            return (P2IN & BIT5); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5);
        case SENSOR12:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN2);*/
                P2DIR &= ~BIT2;
                P2OUT |= BIT2;
                P2REN |= BIT2;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2);*/
                P2DIR &= ~BIT2;
                P2REN &= ~BIT2;
                P2OUT &= ~BIT2;
            }
            return (P2IN & BIT2); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN2);
        case SENSOR13:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN1);*/
                P2DIR &= ~BIT1;
                P2OUT |= BIT1;
                P2REN |= BIT1;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);*/
                P2DIR &= ~BIT1;
                P2REN &= ~BIT1;
                P2OUT &= ~BIT1;
            }
            return (P2IN & BIT1); //return GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN1);
        case SENSOR14:
            if (SENS[SENS_NUMBER-SENSOR1].SCTL & SENS_PULL)
            {
                /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN6);*/
                P1DIR &= ~BIT6;
                P1OUT |= BIT6;
                P1REN |= BIT6;
            } else
            {
                /*GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);*/
                P1DIR &= ~BIT6;
                P1REN &= ~BIT6;
                P1OUT &= ~BIT6;
            }
            return (P1IN & BIT6); //return GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6);
        case SENSOR15:
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_10;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR16:
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN7);*/
            P6SEL |= BIT7;
            P6DIR &= ~BIT7;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_7;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR17:
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN6);*/
            P6SEL |= BIT6;
            P6DIR &= ~BIT6;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_6;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR18:
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_11;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        default:
            return 0x00;
    }
}

// Read analog value of sensor
uint32_t SENSOR_read_analog(uint8_t SENS_NUMBER)
{
    switch (SENS_NUMBER)
    {
        case SENSOR1:
            P4OUT &= ~BIT5; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN5);
            P4DIR |= BIT5; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN5);
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN5);*/
            P6SEL |= BIT5;
            P6DIR &= ~BIT5;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_5;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR2:
            P4OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN4);
            P4DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN4);
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN4);*/
            P6SEL |= BIT4;
            P6DIR &= ~BIT4;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_4;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR3:
            P4OUT &= ~BIT3; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN3);
            P4DIR |= BIT3; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN3);
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN3);*/
            P6SEL |= BIT3;
            P6DIR &= ~BIT3;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_3;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR4:
            P4OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
            P4DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN2);*/
            P6SEL |= BIT2;
            P6DIR &= ~BIT2;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_2;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR5:
            P3OUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
            P3DIR |= BIT2; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN1);*/
            P6SEL |= BIT1;
            P6DIR &= ~BIT1;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_1;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR6:
            P3OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN4);
            P3DIR |= BIT4; //GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);
            //GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN0);
            P6SEL |= BIT0;
            P6DIR &= ~BIT0;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_0;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
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
        case SENSOR15:
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_10;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR16:
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN7);*/
            P6SEL |= BIT7;
            P6DIR &= ~BIT7;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_7;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR17:
            /*GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,GPIO_PIN6);*/
            P6SEL |= BIT6;
            P6DIR &= ~BIT6;
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_6;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        case SENSOR18:
            ADC10CTL0 &= ~ADC10ENC;
            ADC10MCTL0 = ADC10INCH_11;
            ADC10CTL0 |= ADC10SC + ADC10ENC;
            while (ADC10CTL1 & ADC10BUSY)
                ;
            return ADC10MEM0;
        default:
            return 0x00;
    }
}
