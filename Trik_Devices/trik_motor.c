/*
 * Trik_Motor.c
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_devices.h"
#include "trik_motor.h"
#include "trik_encoder.h"

//Motor enable and start
void MOTOR_start(uint8_t MOT_NUMBER)
{
    if (!(isSlotBusy(MOT_NUMBER)))
    {
        reseveSlot(MOT_NUMBER);
        switch (MOT_NUMBER)
        {
            case MOTOR1:
                if (!(MOT[MOT_NUMBER].MCTL & MOT_BACK))
                {
                    P5OUT |= BIT4; //GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
                    P5OUT &= ~BIT5; //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5);
                } else
                {
                    P5OUT |= BIT5; //GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN5);
                    P5OUT &= ~BIT4; //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
                }
                if (MOT[MOT_NUMBER].MCTL & MOT_POWER)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCR1 = MOT[MOT_NUMBER].MDUT;           // CCR1 PWM duty cycle
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                P5DIR |= BIT4+BIT5; //GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2);*/
                P1SEL |= BIT2;
                P1DIR |= BIT2;
                //Overcurrent interrupt init
                P1DIR &= ~BIT1;
                P1IES &= ~BIT1;
                P1IE |= BIT1;
                P1IFG &= ~BIT1;
                break;
            case MOTOR2:
                if (!(MOT[MOT_NUMBER].MCTL & MOT_BACK))
                {
                    P4OUT |= BIT0; //GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
                    P4OUT &= ~BIT1; //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                } else
                {
                    P4OUT |= BIT1; //GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
                    P4OUT &= ~BIT0; //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
                }
                if (MOT[MOT_NUMBER].MCTL & MOT_POWER)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCR2 = MOT[MOT_NUMBER].MDUT;           // CCR2 PWM duty cycle
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                P4DIR |= BIT0+BIT1; //GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN1);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);*/
                P1SEL |= BIT3;
                P1DIR |= BIT3;
                //Overcurrent interrupt init
                P2DIR &= ~BIT6;
                P2IES &= ~BIT6;
                P2IE |= BIT6;
                P2IFG &= ~BIT6;
                break;
            case MOTOR3:
                if (!(MOT[MOT_NUMBER].MCTL & MOT_BACK))
                {
                    PJOUT |= BIT0; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN0);
                    PJOUT &= ~BIT1; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN1);
                } else
                {
                    PJOUT |= BIT1; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN1);
                    PJOUT &= ~BIT0; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0);
                }
                if (MOT[MOT_NUMBER].MCTL & MOT_POWER)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCR3 = MOT[MOT_NUMBER].MDUT;           // CCR3 PWM duty cycle
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                PJDIR |= BIT0+BIT1; //GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN4);*/
                P1SEL |= BIT4;
                P1DIR |= BIT4;
                //Overcurrent interrupt init
                P1DIR &= ~BIT7;
                P1IES &= ~BIT7;
                P1IE |= BIT7;
                P1IFG &= ~BIT7;
                break;
            case MOTOR4:
                if (!(MOT[MOT_NUMBER].MCTL & MOT_BACK))
                {
                    PJOUT |= BIT2; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN2);
                    PJOUT &= ~BIT3; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN3);
                } else
                {
                    PJOUT |= BIT3; //GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN3);
                    PJOUT &= ~BIT2; //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2);
                }
                if (MOT[MOT_NUMBER].MCTL & MOT_POWER)
                {
                    if (MOT[MOT_NUMBER].MCTL & MOT_AUTO)
                        MOT[MOT_NUMBER].MVAL = 0;
                    TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                    TA0CCR4 = MOT[MOT_NUMBER].MDUT;           // CCR4 PWM duty cycle
                } else
                {
                    MOTOR_stop(MOT_NUMBER);
                }
                PJDIR |= BIT2+BIT3; //GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN2 | GPIO_PIN3);
                /*GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN5);*/
                P1SEL |= BIT5;
                P1DIR |= BIT5;
                //Overcurrent interrupt init
                P2DIR &= ~BIT7;
                P2IES &= ~BIT7;
                P2IE |= BIT7;
                P2IFG &= ~BIT7;
                break;
            default:
                break;
        }
    }
}

//Motor disable
void MOTOR_disable(uint8_t MOT_NUMBER)
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

//Motor stop/brake
void MOTOR_stop(uint8_t MOT_NUMBER)
{
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            if (MOT[MOT_NUMBER].MCTL & MOT_BRAKE)
            {
                P5OUT &= ~(BIT4+BIT5); //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4|GPIO_PIN5);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
                TA0CCR1 = MOT[MOT_NUMBER].MPER-1;         // CCR1 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
                TA0CCR1 = 0x0001;                         // CCR1 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            }
            break;
        case MOTOR2:
            if (MOT[MOT_NUMBER].MCTL & MOT_BRAKE)
            {
                P4OUT &= ~(BIT0+BIT1); //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
                TA0CCR2 = MOT[MOT_NUMBER].MPER-1;         // CCR2 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
                TA0CCR2 = 0x0001;                         // CCR2 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            }
            break;
        case MOTOR3:
            if (MOT[MOT_NUMBER].MCTL & MOT_BRAKE)
            {
                PJOUT &= ~(BIT0+BIT1); //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0|GPIO_PIN1);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL3 = OUTMOD_7;                      // CCR3 reset/set
                TA0CCR3 = MOT[MOT_NUMBER].MPER-1;         // CCR3 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL3 = OUTMOD_7;                      // CCR3 reset/set
                TA0CCR3 = 0x0001;                         // CCR3 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            }
            break;
        case MOTOR4:
            if (MOT[MOT_NUMBER].MCTL & MOT_BRAKE)
            {
                PJOUT &= ~(BIT2+BIT3); //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2|GPIO_PIN3);
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL4 = OUTMOD_7;                      // CCR4 reset/set
                TA0CCR4 = MOT[MOT_NUMBER].MPER-1;         // CCR4 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            } else
            {
                TA0CCR0 = MOT[MOT_NUMBER].MPER;           // PWM Period
                TA0CCTL4 = OUTMOD_7;                      // CCR4 reset/set
                TA0CCR4 = 0x0001;                         // CCR4 PWM duty cycle
                TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;         // SMCLK, up mode, clear TAR
            }
            break;
        default:
            break;
    }
    MOT[MOT_NUMBER].MCTL &= ~(MOT_POWER + MOT_AUTO);
}

