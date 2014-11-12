/*
 * trik_encoder.c
 *
 *  Created on: November 7, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <math.h>
#include "trik_devices.h"
#include "trik_encoder.h"
#include "trik_motor.h"
#include "driverlib.h"

//API functions
void ENCODER_enableController(uint8_t ENC_NUMBER)
{
    //PB_EN
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN3);
    if (busy_table[ENC_NUMBER]==NNONE)
    {
        busy_table[ENC_NUMBER]=ENC_NUMBER;
        ENC[ENC_NUMBER-ENCODER1].ENC_EN = ENABLE;
        switch (ENC_NUMBER)
        {
            case ENCODER1:
                GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
                GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
                GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3,GPIO_LOW_TO_HIGH_TRANSITION);
                GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
                break;
            case ENCODER2:
                GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
                GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
                GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
                //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
                GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN4,GPIO_LOW_TO_HIGH_TRANSITION);
                //GPIO_interruptEdgeSelect(GPIO_PORT_P1,GPIO_PIN0,GPIO_LOW_TO_HIGH_TRANSITION);
                GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
                //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0);
                break;
            case ENCODER4:
                GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
                GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
                GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
                //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
                GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN1,GPIO_LOW_TO_HIGH_TRANSITION);
                //GPIO_interruptEdgeSelect(GPIO_PORT_P1,GPIO_PIN6,GPIO_LOW_TO_HIGH_TRANSITION);
                GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
                //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN6);
                break;
            case ENCODER3:
                GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
                GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
                GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5,GPIO_LOW_TO_HIGH_TRANSITION);
                GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
                break;
            default:;
        }
    }
}

void ENCODER_disableController(uint8_t ENC_NUMBER)
{
    busy_table[ENC_NUMBER]=NNONE;
    ENC[ENC_NUMBER-ENCODER1].ENC_EN = DISABLE;
    switch (ENC_NUMBER)
    {
        case ENCODER1:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            break;
        case ENCODER2:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
            break;
        case ENCODER4:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
            break;
        case ENCODER3:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            break;
        default:;
    }
}

void ENCODER_enablePullup(uint8_t ENC_NUMBER)
{
    ENC[ENC_NUMBER-ENCODER1].ENC_PUP = ENABLE;
    switch (ENC_NUMBER)
    {
        case ENCODER1:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            break;
        case ENCODER2:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN4);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0);
            break;
        case ENCODER4:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN1);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN6);
            break;
        case ENCODER3:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            break;
        default:;
    }
}

void ENCODER_disablePullup(uint8_t ENC_NUMBER)
{
    ENC[ENC_NUMBER-ENCODER1].ENC_PUP = DISABLE;
    switch (ENC_NUMBER)
    {
        case ENCODER1:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            break;
        case ENCODER2:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0);
            break;
        case ENCODER4:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN6);
            break;
        case ENCODER3:
            GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            break;
        default:;
    }
}

//Handler
uint8_t ENCODER_hadler(uint8_t ENC_NUMBER)
{
    if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x8000)
    {
        //Enable/disable
        if (!(ENC[ENC_NUMBER-ENCODER1].ENC_EN)) ENCODER_enableController(ENC_NUMBER);

        //Async/single read mode
        if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x4000)
        {
            ENC[ENC_NUMBER-ENCODER1].ENC_MOD = ENABLE;
        }
        else
        {
            ENC[ENC_NUMBER-ENCODER1].ENC_MOD = DISABLE;
        }

        //1-wire/2-wire mode
        if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x2000)
        {
            ENC[ENC_NUMBER-ENCODER1].ENC_TYP = WIRE2;
        }
        else
        {
            ENC[ENC_NUMBER-ENCODER1].ENC_TYP = WIRE1;
        }


        //Pull up resistors enable/disable
        if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x1000)
        {
            ENCODER_enablePullup(ENC_NUMBER);
        }
        else
        {
            ENCODER_disablePullup(ENC_NUMBER);
        }

        return 0x00;
    }
    else
    {
        if (ENC[ENC_NUMBER-ENCODER1].ENC_EN) ENCODER_disableController(ENC_NUMBER);
        return 0x00;
    }
}

//Interrupts
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(PORT1_VECTOR)))
#endif
void PORT1_ISR(void)
{
    /*
    if (ENC[ENCODER2-ENCODER1].ENC_TYP==WIRE1)
    {
        if (GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN0)) ENC[ENCODER2-ENCODER1].EVAL++;
    }
    if (ENC[ENCODER4-ENCODER1].ENC_TYP==WIRE1)
    {
        if (GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN6)) ENC[ENCODER4-ENCODER1].EVAL++;
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0|GPIO_PIN6);
    */
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(PORT2_VECTOR)))
#endif
void PORT2_ISR(void)
{
        //JB1
        if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN0))
        {
            if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3))
            {
                if (ENC[ENCODER1-ENCODER1].ENC_TYP==WIRE2)
                    ENC[ENCODER1-ENCODER1].EVAL--;
                else
                    ENC[ENCODER1-ENCODER1].EVAL++;
            }
            else
            {
                ENC[ENCODER1-ENCODER1].EVAL++;
            }
            if (MOT[MOTOR1].MOT_MOD==ANGLE_MODE)
            {
                MOT[MOTOR1].MVAL++;
                if ((MOT[MOTOR1].MVAL>MOT[MOTOR1].MANG)) MOTOR_stop(MOTOR1);
            }
        }

        //JB2
        if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN4))
        {
            if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN0))
            {
                if (ENC[ENCODER2-ENCODER1].ENC_TYP==WIRE2)
                    ENC[ENCODER2-ENCODER1].EVAL--;
                else ENC[ENCODER2-ENCODER1].EVAL++;
            }
            else
            {
                ENC[ENCODER2-ENCODER1].EVAL++;
            }
            if (MOT[MOTOR2].MOT_MOD==ANGLE_MODE)
            {
                MOT[MOTOR2].MVAL++;
                if ((MOT[MOTOR2].MVAL>MOT[MOTOR2].MANG)) MOTOR_stop(MOTOR2);
            }
        }

        //JB3
        if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN5))
        {
            if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN2))
            {
                if (ENC[ENCODER3-ENCODER1].ENC_TYP==WIRE2)
                    ENC[ENCODER3-ENCODER1].EVAL--;
                else ENC[ENCODER3-ENCODER1].EVAL++;
            }
            else
            {
                ENC[ENCODER3-ENCODER1].EVAL++;
            }
            if (MOT[MOTOR3].MOT_MOD==ANGLE_MODE)
            {
                MOT[MOTOR3].MVAL++;
                if ((MOT[MOTOR3].MVAL>MOT[MOTOR3].MANG)) MOTOR_stop(MOTOR3);
            }
        }

        //JB4
        if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN1))
        {
            if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN6))
            {
                if (ENC[ENCODER4-ENCODER1].ENC_TYP==WIRE2)
                    ENC[ENCODER4-ENCODER1].EVAL--;
                else ENC[ENCODER4-ENCODER1].EVAL++;
            }
            else
            {
                ENC[ENCODER4-ENCODER1].EVAL++;
            }
            if (MOT[MOTOR4].MOT_MOD==ANGLE_MODE)
            {
                MOT[MOTOR4].MVAL++;
                if ((MOT[MOTOR4].MVAL>MOT[MOTOR4].MANG)) MOTOR_stop(MOTOR4);
            }
        }
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5);
}


