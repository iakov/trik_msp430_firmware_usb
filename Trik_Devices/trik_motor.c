/*
 * Trik_Motor.c
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_devices.h"
#include "trik_motor.h"
#include "driverlib.h"

void MOTOR_enableController(uint8_t MOT_NUMBER)
{
    if (!(isSlotBusy(MOT_NUMBER)))
    {
        reseveSlot(MOT_NUMBER);
        switch (MOT_NUMBER)
        {
            case MOTOR1:
                if (MOT[MOT_NUMBER].MOT_DIR==FORWARD)
                {
                    P5OUT |= BIT4; //GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
                    P5OUT &= ~BIT5; //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5);
                } else
                {
                    P5OUT |= BIT5; //GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN5);
                    P5OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
                }
                if (MOT[MOT_NUMBER].MOT_PWR==ENABLE)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
                    TA0CCR1 = MOT[MOT_NUMBER].MDUT;           // CCR1 PWM duty cycle
                    TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                P5DIR |= BIT4+BIT5; //GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2);*/
                P1SEL |= BIT2;
                P1DIR |= BIT2;
                P1DIR &= ~BIT1; //GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN1);
                break;
            case MOTOR2:
                if (MOT[MOT_NUMBER].MOT_DIR==FORWARD)
                {
                    P4OUT |= BIT0; //GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
                    P4OUT &= ~BIT1; //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                } else
                {
                    P4OUT |= BIT1; //GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
                    P4OUT &= ~BIT0; //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
                }
                if (MOT[MOT_NUMBER].MOT_PWR==ENABLE)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
                    TA0CCR2 = MOT[MOT_NUMBER].MDUT;           // CCR2 PWM duty cycle
                    TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                P4DIR |= BIT0+BIT1; //GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN1);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);*/
                P1SEL |= BIT3;
                P1DIR |= BIT3;
                P2DIR &= ~BIT6; //GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN6);
                break;
            case MOTOR3:
                if (MOT[MOT_NUMBER].MOT_DIR==FORWARD)
                {
                    PJOUT |= BIT0; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN0);
                    PJOUT &= ~BIT1; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN1);
                } else
                {
                    PJOUT |= BIT1; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN1);
                    PJOUT &= ~BIT0; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0);
                }
                if (MOT[MOT_NUMBER].MOT_PWR==ENABLE)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCTL3 = OUTMOD_7;                      // CCR3 reset/set
                    TA0CCR3 = MOT[MOT_NUMBER].MDUT;           // CCR3 PWM duty cycle
                    TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                PJDIR |= BIT0+BIT1; //GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN4);*/
                P1SEL |= BIT4;
                P1DIR |= BIT4;
                P1DIR &= ~BIT7; //GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN7);
                break;
            case MOTOR4:
                if (MOT[MOT_NUMBER].MOT_DIR==FORWARD)
                {
                    PJOUT |= BIT2; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN2);
                    PJOUT &= ~BIT3; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN3);
                } else
                {
                    PJOUT |= BIT3; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN3);
                    PJOUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2);
                }
                if (MOT[MOT_NUMBER].MOT_PWR==ENABLE)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCTL4 = OUTMOD_7;                      // CCR4 reset/set
                    TA0CCR4 = MOT[MOT_NUMBER].MDUT;           // CCR4 PWM duty cycle
                    TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                PJDIR |= BIT2+BIT3; //GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN2 | GPIO_PIN3);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN5);*/
                P1SEL |= BIT5;
                P1DIR |= BIT5;
                P2DIR &= ~BIT7; //GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN7);
                break;
            default:
                break;
        }
    }
}

void MOTOR_disableController(uint8_t MOT_NUMBER)
{
    releaseSlot(MOT_NUMBER);
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            P5DIR &= ~(BIT4+BIT5); //GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5);
            P1DIR &= ~BIT2; //GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN2);
            break;
        case MOTOR2:
            P4DIR &= ~(BIT0+BIT1); //GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN1);
            P1DIR &= ~BIT3; //GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN3);
            break;
        case MOTOR3:
            PJDIR &= ~(BIT0+BIT1); //GPIO_setAsInputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1);
            P1DIR &= ~BIT4; //GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN4);
            break;
        case MOTOR4:
            PJDIR &= ~(BIT2+BIT3); //GPIO_setAsInputPin(GPIO_PORT_PJ, GPIO_PIN2 | GPIO_PIN3);
            P1DIR &= ~BIT5; //GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN5);
            break;
        default:
            break;
    }
}

void MOTOR_stop(uint8_t MOT_NUMBER)
{
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                P5OUT &= ~(BIT4+BIT5); //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4|GPIO_PIN5);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
                TA0CCR1 = MOT[MOT_NUMBER].MPER-1;         // CCR1 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
                TA0CCR1 = 0x0001;                         // CCR1 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            }
            break;
        case MOTOR2:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                P4OUT &= ~(BIT0+BIT1); //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
                TA0CCR2 = MOT[MOT_NUMBER].MPER-1;         // CCR2 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
                TA0CCR2 = 0x0001;                         // CCR2 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            }
            break;
        case MOTOR3:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                PJOUT &= ~(BIT0+BIT1); //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0|GPIO_PIN1);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL3 = OUTMOD_7;                      // CCR3 reset/set
                TA0CCR3 = MOT[MOT_NUMBER].MPER-1;         // CCR3 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL3 = OUTMOD_7;                      // CCR3 reset/set
                TA0CCR3 = 0x0001;                         // CCR3 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            }
            break;
        case MOTOR4:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                PJOUT &= ~(BIT2+BIT3); //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2|GPIO_PIN3);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL4 = OUTMOD_7;                      // CCR4 reset/set
                TA0CCR4 = MOT[MOT_NUMBER].MPER-1;         // CCR4 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL4 = OUTMOD_7;                      // CCR4 reset/set
                TA0CCR4 = 0x0001;                         // CCR4 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
            }
            break;
        default:
            break;
    }
    MOT[MOT_NUMBER].MOT_PWR = DISABLE;
    MOT[MOT_NUMBER].MCTL &= ~MOT_AUTO;
}

void MOTOR_handler(uint8_t MOT_NUMBER)
{
    //Forward/backward
    if (MOT[MOT_NUMBER].MCTL & 0x0010)
        MOT[MOT_NUMBER].MOT_DIR = BACKWARD;
    else
        MOT[MOT_NUMBER].MOT_DIR = FORWARD;
    //Fast brake enable/disable
    if (MOT[MOT_NUMBER].MCTL & 0x0008)
        MOT[MOT_NUMBER].MOT_BRK = ENABLE;
    else
        MOT[MOT_NUMBER].MOT_BRK = DISABLE;
    //Start/stop
    if (MOT[MOT_NUMBER].MCTL & 0x0003)
        MOT[MOT_NUMBER].MOT_PWR=ENABLE;
    else
        MOT[MOT_NUMBER].MOT_PWR=DISABLE;
    //Enable/disable
    if (MOT[MOT_NUMBER].MCTL & MOT_ENABLE)
        MOTOR_enableController(MOT_NUMBER);
    else
        MOTOR_disableController(MOT_NUMBER);

    MOT[MOT_NUMBER].MSTA = MOT_NO_ERROR;
}
