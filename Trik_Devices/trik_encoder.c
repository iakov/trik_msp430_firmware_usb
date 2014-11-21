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

void ENCODER_enableController(uint8_t ENC_NUMBER)
{
    if ((busy_table[ENC_NUMBER]==NNONE) || (busy_table[ENC_NUMBER]==ENC_NUMBER))
    {
        busy_table[ENC_NUMBER]=ENC_NUMBER;
        ENC[ENC_NUMBER-ENCODER1].ENC_EN = ENABLE;
        switch (ENC_NUMBER)
        {
            case ENCODER1:
                if (ENC[ENC_NUMBER-ENCODER1].ENC_PUP==ENABLE)
                {
                    P2DIR &= ~(BIT0+BIT3); P2OUT |= BIT0+BIT3; P2REN |= BIT0+BIT3; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
                }
                else
                {
                    P2DIR &= ~(BIT0+BIT3); P2REN &= ~(BIT0+BIT3); //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
                }
                P2IE |= BIT0+BIT3; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
                if (ENC[ENC_NUMBER-ENCODER1].ENC_EDG==RIS_EDGE)
                    P2IES &= ~(BIT0+BIT3); //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3,GPIO_LOW_TO_HIGH_TRANSITION);
                else
                    P2IES |= BIT0+BIT3; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3,GPIO_HIGH_TO_LOW_TRANSITION);
                P2IFG &= ~(BIT0+BIT3); //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
                break;
            case ENCODER2:
                if (ENC[ENC_NUMBER-ENCODER1].ENC_PUP==ENABLE)
                {
                    P1DIR &= ~BIT0; P1OUT |= BIT0; P1REN |= BIT0; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN0);
                    P2DIR &= ~BIT4; P2OUT |= BIT4; P2REN |= BIT4; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN4);
                } else
                {
                    P1DIR &= ~BIT0; P1REN &= ~BIT0; //GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
                    P2DIR &= ~BIT4; P2REN &= ~BIT4; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
                }
                P2IE |= BIT4; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
                //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
                if (ENC[ENC_NUMBER-ENCODER1].ENC_EDG==RIS_EDGE)
                    P2IES &= ~BIT4; // GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN4,GPIO_LOW_TO_HIGH_TRANSITION);
                else
                    P2IES |= BIT4; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN4,GPIO_HIGH_TO_LOW_TRANSITION);
                //GPIO_interruptEdgeSelect(GPIO_PORT_P1,GPIO_PIN0,GPIO_LOW_TO_HIGH_TRANSITION);
                P2IFG &= ~BIT4; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
                //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0);
                break;
            case ENCODER4:
                if (ENC[ENC_NUMBER-ENCODER1].ENC_PUP==ENABLE)
                {
                    P1DIR &= ~BIT6; P1OUT |= BIT6; P1REN |= BIT6;//GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN6);
                    P2DIR &= ~BIT1; P2OUT |= BIT1; P2REN |= BIT1;//GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN1);
                } else
                {
                    P1DIR &= ~BIT6; P1REN &= ~BIT6; //GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
                    P2DIR &= ~BIT1; P2REN &= ~BIT1; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
                }
                P2IE |= BIT1; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
                //GPIO_enableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
                if (ENC[ENC_NUMBER-ENCODER1].ENC_EDG==RIS_EDGE)
                    P2IES &= ~BIT1; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN1,GPIO_LOW_TO_HIGH_TRANSITION);
                else
                    P2IES |= BIT1; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN1,GPIO_HIGH_TO_LOW_TRANSITION);
                //GPIO_interruptEdgeSelect(GPIO_PORT_P1,GPIO_PIN6,GPIO_LOW_TO_HIGH_TRANSITION);
                P2IFG &= ~BIT1; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
                //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN6);
                break;
            case ENCODER3:
                if (ENC[ENC_NUMBER-ENCODER1].ENC_PUP==ENABLE)
                {
                    P2DIR &= ~(BIT0+BIT3); P2OUT |= BIT2+BIT5; P2REN |= BIT2+BIT5; //GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
                }
                else
                {
                    P2DIR &= ~(BIT2+BIT5); P2REN &= ~(BIT2+BIT5); //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
                }
                P2IE |= BIT2+BIT5; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
                if (ENC[ENC_NUMBER-ENCODER1].ENC_EDG==RIS_EDGE)
                    P2IES &= ~(BIT2+BIT5); //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5,GPIO_LOW_TO_HIGH_TRANSITION);
                else
                    P2IES |= BIT2+BIT5; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5,GPIO_HIGH_TO_LOW_TRANSITION);
                P2IFG &= ~(BIT2+BIT5); //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
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
            P2IE &= ~(BIT0+BIT3); //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            P2IFG &= ~(BIT0+BIT3); //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            P2DIR &= ~(BIT0+BIT3); P2REN &= ~(BIT0+BIT3); //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);
            break;
        case ENCODER2:
            P2IE &= ~BIT4; //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN0);
            P2IFG &= ~BIT4; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0);
            P1DIR &= ~BIT0; P1REN &= ~BIT0; //GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);
            P2DIR &= ~BIT4; P2REN &= ~BIT4; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);
            break;
        case ENCODER4:
            P2IE &= ~BIT1; //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_disableInterrupt(GPIO_PORT_P1,GPIO_PIN6);
            P2IFG &= ~BIT1; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
            //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN6);
            P1DIR &= ~BIT6; P1REN &= ~BIT6; //GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
            P2DIR &= ~BIT1; P2REN &= ~BIT1; //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);
            break;
        case ENCODER3:
            P2IE &= ~(BIT2+BIT5); //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            P2IFG &= ~(BIT2+BIT5); //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            P2DIR &= ~(BIT2+BIT5); P2REN &= ~(BIT2+BIT5); //GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);
            break;
        default:;
    }
}

void ENCODER_hadler(uint8_t ENC_NUMBER)
{
    //Async/single read mode
    if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x4000)
        ENC[ENC_NUMBER-ENCODER1].ENC_MOD = ENABLE;
    else
        ENC[ENC_NUMBER-ENCODER1].ENC_MOD = DISABLE;
    //1-wire/2-wire mode
    if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x2000)
        ENC[ENC_NUMBER-ENCODER1].ENC_TYP = WIRE2;
    else
        ENC[ENC_NUMBER-ENCODER1].ENC_TYP = WIRE1;
    //Pull up resistors enable/disable
    if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x1000)
        ENC[ENC_NUMBER-ENCODER1].ENC_PUP = ENABLE;
    else
        ENC[ENC_NUMBER-ENCODER1].ENC_PUP = DISABLE;
    //Edge select
    if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x0800)
        ENC[ENC_NUMBER-ENCODER1].ENC_EDG = FAL_EDGE;
    else
        ENC[ENC_NUMBER-ENCODER1].ENC_EDG = RIS_EDGE;
    //Enable/disable
    if (ENC[ENC_NUMBER-ENCODER1].ECTL & 0x8000)
        ENCODER_enableController(ENC_NUMBER);
    else
        ENCODER_disableController(ENC_NUMBER);

    ENC[ENC_NUMBER-ENCODER1].ESTA = ENC_NO_ERROR;
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
    */
    P1IFG &= ~(BIT0+BIT6); //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0|GPIO_PIN6);
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
    if (P2IFG & BIT0) //if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN0))
    {
        if (P2IN & BIT3) //if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3))
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
    if (P2IFG & BIT4) //if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN4))
    {
        if (P1IN & BIT0) //if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN0))
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
    if (P2IFG & BIT5) //if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN5))
    {
        if (P2IN & BIT2) //if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN2))
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
    if (P2IFG & BIT1) //if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN1))
    {
        if (P1IN & BIT6) //if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN6))
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

    P2IFG &= ~(BIT0+BIT1+BIT2+BIT3+BIT4+BIT5); //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5);
}


