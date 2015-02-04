/*
 * trik_encoder.c
 *
 *  Created on: November 7, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_encoder.h"
#include "trik_motor.h"

//Enable encoder
void ENCODER_enableController(uint8_t ENC_NUMBER)
{
    if (!(isSlotBusy(ENC_NUMBER)))
    {
        reseveSlot(ENC_NUMBER);
        switch (ENC_NUMBER)
        {
            case ENCODER1:
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_PUPEN)
                {
                    /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);*/
                    P2DIR &= ~(BIT0+BIT3);
                    P2OUT |= BIT0+BIT3;
                    P2REN |= BIT0+BIT3;
                }
                else
                {
                    /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);*/
                    P2DIR &= ~(BIT0+BIT3);
                    P2REN &= ~(BIT0+BIT3);
                    P2OUT &= ~(BIT0+BIT3);
                }
                P2IE |= BIT0; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN0);
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_FALL)
                    P2IES |= BIT0; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN0,GPIO_HIGH_TO_LOW_TRANSITION);
                else
                    P2IES &= ~BIT0; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN0,GPIO_LOW_TO_HIGH_TRANSITION);
                P2IFG &= ~BIT0; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0);
                break;
            case ENCODER2:
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_PUPEN)
                {
                    /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN0);*/
                    P1DIR &= ~BIT0;
                    P1OUT |= BIT0;
                    P1REN |= BIT0;
                    /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN4);*/
                    P2DIR &= ~BIT4;
                    P2OUT |= BIT4;
                    P2REN |= BIT4;
                } else
                {
                    /*GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);*/
                    P1DIR &= ~BIT0;
                    P1REN &= ~BIT0;
                    P1OUT &= ~BIT0;
                    /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);*/
                    P2DIR &= ~BIT4;
                    P2REN &= ~BIT4;
                    P2OUT &= ~BIT4;
                }
                P2IE |= BIT4; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_FALL)
                    P2IES |= BIT4; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN4,GPIO_HIGH_TO_LOW_TRANSITION);
                else
                    P2IES &= ~BIT4; // GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN4,GPIO_LOW_TO_HIGH_TRANSITION);
                P2IFG &= ~BIT4; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
                break;
            case ENCODER4:
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_PUPEN)
                {
                    /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);*/
                    P2DIR &= ~(BIT2+BIT5);
                    P2OUT |= BIT2+BIT5;
                    P2REN |= BIT2+BIT5;
                }
                else
                {
                    /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);*/
                    P2DIR &= ~(BIT2+BIT5);
                    P2REN &= ~(BIT2+BIT5);
                    P2OUT &= ~(BIT2+BIT5);
                }
                P2IE |= BIT5; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN5);
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_FALL)
                    P2IES |= BIT5; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN5,GPIO_HIGH_TO_LOW_TRANSITION);
                else
                    P2IES &= ~BIT5; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN5,GPIO_LOW_TO_HIGH_TRANSITION);
                P2IFG &= ~BIT5; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN5);
                break;
            case ENCODER3:
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_PUPEN)
                {
                    /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P1,GPIO_PIN6);*/
                    P1DIR &= ~BIT6;
                    P1OUT |= BIT6;
                    P1REN |= BIT6;
                    /*GPIO_setAsInputPinWithPullUpresistor(GPIO_PORT_P2,GPIO_PIN1);*/
                    P2DIR &= ~BIT1;
                    P2OUT |= BIT1;
                    P2REN |= BIT1;
                } else
                {
                    /*GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);*/
                    P1DIR &= ~BIT6;
                    P1REN &= ~BIT6;
                    P1OUT &= ~BIT6;
                    /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);*/
                    P2DIR &= ~BIT1;
                    P2REN &= ~BIT1;
                    P2OUT &= ~BIT1;
                }
                P2IE |= BIT1; //GPIO_enableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
                if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_FALL)
                    P2IES |= BIT1; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN1,GPIO_HIGH_TO_LOW_TRANSITION);
                else
                    P2IES &= ~BIT1; //GPIO_interruptEdgeSelect(GPIO_PORT_P2,GPIO_PIN1,GPIO_LOW_TO_HIGH_TRANSITION);
                P2IFG &= ~BIT1; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
                break;
            default:
                break;
        }
    }
}

//Disable encoder
void ENCODER_disableController(uint8_t ENC_NUMBER)
{
    releaseSlot(ENC_NUMBER);
    switch (ENC_NUMBER)
    {
        case ENCODER1:
            P2IE &= ~BIT0; //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN0);
            P2IFG &= ~BIT0; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0);
            /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN3);*/
            P2DIR &= ~(BIT0+BIT3);
            P2REN &= ~(BIT0+BIT3);
            P2OUT &= ~(BIT0+BIT3);
            break;
        case ENCODER2:
            P2IE &= ~BIT4; //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN4);
            P2IFG &= ~BIT4; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN4);
            /*GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN0);*/
            P1DIR &= ~BIT0;
            P1REN &= ~BIT0;
            P1OUT &= ~BIT0;
            /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN4);*/
            P2DIR &= ~BIT4;
            P2REN &= ~BIT4;
            P2OUT &= ~BIT4;
            break;
        case ENCODER4:
            P2IE &= ~BIT5; //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN5);
            P2IFG &= ~BIT5; //GPIO_clearInterruptFlag(GPIO_PORT_GPIO_PIN5);
            /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN2|GPIO_PIN5);*/
            P2DIR &= ~(BIT2+BIT5);
            P2REN &= ~(BIT2+BIT5);
            P2OUT &= ~(BIT2+BIT5);
            break;
        case ENCODER3:
            P2IE &= ~BIT1; //GPIO_disableInterrupt(GPIO_PORT_P2,GPIO_PIN1);
            P2IFG &= ~BIT1; //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN1);
            /*GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);*/
            P1DIR &= ~BIT6;
            P1REN &= ~BIT6;
            P1OUT &= ~BIT6;
            /*GPIO_setAsInputPin(GPIO_PORT_P2,GPIO_PIN1);*/
            P2DIR &= ~BIT1;
            P2REN &= ~BIT1;
            P2OUT &= ~BIT1;
            break;
        default:
            break;
    }
}

//Encoders handler
void ENCODER_handler(uint8_t ENC_NUMBER)
{
    //Enable/disable encoder
    if (ENC[ENC_NUMBER-ENCODER1].ECTL & ENC_ENABLE)
        ENCODER_enableController(ENC_NUMBER);
    else
        ENCODER_disableController(ENC_NUMBER);

    //Status register
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
    //M1 overcurrent interrupt
    if (P1IFG & BIT1)
        MOT[MOTOR1].MERR++;

    //M3 overcurrent interrupt
    if (P1IFG & BIT7)
        MOT[MOTOR3].MERR++;

    P1IFG &= ~(BIT0+BIT6); //GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0|GPIO_PIN6);
    P1IFG &= ~(BIT1+BIT7); //For overcurrent
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
            if (ENC[ENCODER1-ENCODER1].ECTL & ENC_2WIRES)
                ENC[ENCODER1-ENCODER1].EVAL--;
            else
                ENC[ENCODER1-ENCODER1].EVAL++;
        }
        else
        {
            ENC[ENCODER1-ENCODER1].EVAL++;
        }
        if ((MOT[MOTOR1].MCTL & MOT_AUTO) && (MOT[MOTOR1].MCTL & MOT_ANGLE))
        {
            MOT[MOTOR1].MVAL++;
            if ((MOT[MOTOR1].MVAL>MOT[MOTOR1].MANG))
                MOTOR_stop(MOTOR1);
        }
    }

    //JB2
    if (P2IFG & BIT4) //if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN4))
    {
        if (P1IN & BIT0) //if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN0))
        {
            if (ENC[ENCODER2-ENCODER1].ECTL & ENC_2WIRES)
                ENC[ENCODER2-ENCODER1].EVAL--;
            else
                ENC[ENCODER2-ENCODER1].EVAL++;
        }
        else
        {
            ENC[ENCODER2-ENCODER1].EVAL++;
        }
        if ((MOT[MOTOR2].MCTL & MOT_AUTO) && (MOT[MOTOR2].MCTL & MOT_ANGLE))
        {
            MOT[MOTOR2].MVAL++;
            if ((MOT[MOTOR2].MVAL>MOT[MOTOR2].MANG))
                MOTOR_stop(MOTOR2);
        }
    }

    //JB4
    if (P2IFG & BIT5) //if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN5))
    {
        if (P2IN & BIT2) //if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN2))
        {
            if (ENC[ENCODER4-ENCODER1].ECTL & ENC_2WIRES)
                ENC[ENCODER4-ENCODER1].EVAL--;
            else
                ENC[ENCODER4-ENCODER1].EVAL++;
        }
        else
        {
            ENC[ENCODER4-ENCODER1].EVAL++;
        }
        if ((MOT[MOTOR4].MCTL & MOT_AUTO) && (MOT[MOTOR4].MCTL & MOT_ANGLE))
        {
            MOT[MOTOR4].MVAL++;
            if ((MOT[MOTOR4].MVAL>MOT[MOTOR4].MANG))
                MOTOR_stop(MOTOR4);
        }
    }

    //JB3
    if (P2IFG & BIT1) //if (GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN1))
    {
        if (P1IN & BIT6) //if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN6))
        {
            if (ENC[ENCODER3-ENCODER1].ECTL & ENC_2WIRES)
                ENC[ENCODER3-ENCODER1].EVAL--;
            else
                ENC[ENCODER3-ENCODER1].EVAL++;
        }
        else
        {
            ENC[ENCODER3-ENCODER1].EVAL++;
        }
        if ((MOT[MOTOR3].MCTL & MOT_AUTO) && (MOT[MOTOR3].MCTL & MOT_ANGLE))
        {
            MOT[MOTOR3].MVAL++;
            if ((MOT[MOTOR3].MVAL>MOT[MOTOR3].MANG))
                MOTOR_stop(MOTOR3);
        }
    }

    //M2 overcurrent interrupt
    if (P2IFG & BIT6)
        MOT[MOTOR2].MERR++;

    //M4 overcurrent interrupt
    if (P2IFG & BIT7)
        MOT[MOTOR4].MERR++;

    P2IFG &= ~(BIT0+BIT1+BIT4+BIT5); //GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN4|GPIO_PIN5);
    P2IFG &= ~(BIT6+BIT7); //For overcurrent
}


