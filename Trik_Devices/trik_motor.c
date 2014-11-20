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

//API functions
void MOTOR_enableController(uint8_t MOT_NUMBER)
{
    if ((busy_table[MOT_NUMBER]==NNONE) || (busy_table[MOT_NUMBER]==MOT_NUMBER))
    {
        busy_table[MOT_NUMBER]=MOT_NUMBER;
        MOT[MOT_NUMBER].MOT_EN = ENABLE;
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
                    if (MOT[MOT_NUMBER].MOT_MOD!=CONT_MODE) MOT[MOT_NUMBER].MVAL = 0;
                    TIMER_A_generatePWM(TIMER_A0_BASE,
                            TIMER_A_CLOCKSOURCE_SMCLK,
                            TIMER_A_CLOCKSOURCE_DIVIDER_1,
                            MOT[MOT_NUMBER].MPER,
                            TIMER_A_CAPTURECOMPARE_REGISTER_1,
                            TIMER_A_OUTPUTMODE_RESET_SET,
                            MOT[MOT_NUMBER].MDUT);
                } else
                    MOTOR_stop(MOT_NUMBER);
                P5DIR |= BIT4+BIT5; //GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5);
                P1SEL |= BIT2; //GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2);
                GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN1);
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
                    if (MOT[MOT_NUMBER].MOT_MOD!=CONT_MODE) MOT[MOT_NUMBER].MVAL = 0;
                    TIMER_A_generatePWM(TIMER_A0_BASE,
                            TIMER_A_CLOCKSOURCE_SMCLK,
                            TIMER_A_CLOCKSOURCE_DIVIDER_1,
                            MOT[MOT_NUMBER].MPER,
                            TIMER_A_CAPTURECOMPARE_REGISTER_2,
                            TIMER_A_OUTPUTMODE_RESET_SET,
                            MOT[MOT_NUMBER].MDUT);
                } else
                    MOTOR_stop(MOT_NUMBER);
                P4DIR |= BIT0+BIT1; //GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN1);
                P1SEL |= BIT3; //GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);
                GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN6);
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
                    if (MOT[MOT_NUMBER].MOT_MOD!=CONT_MODE) MOT[MOT_NUMBER].MVAL = 0;
                    TIMER_A_generatePWM(TIMER_A0_BASE,
                            TIMER_A_CLOCKSOURCE_SMCLK,
                            TIMER_A_CLOCKSOURCE_DIVIDER_1,
                            MOT[MOT_NUMBER].MPER,
                            TIMER_A_CAPTURECOMPARE_REGISTER_3,
                            TIMER_A_OUTPUTMODE_RESET_SET,
                            MOT[MOT_NUMBER].MDUT);
                } else
                    MOTOR_stop(MOT_NUMBER);
                PJDIR |= BIT0+BIT1; //GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1);
                P1SEL |= BIT4; //GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN4);
                GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN7);
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
                    if (MOT[MOT_NUMBER].MOT_MOD!=CONT_MODE) MOT[MOT_NUMBER].MVAL = 0;
                    TIMER_A_generatePWM(TIMER_A0_BASE,
                            TIMER_A_CLOCKSOURCE_SMCLK,
                            TIMER_A_CLOCKSOURCE_DIVIDER_1,
                            MOT[MOT_NUMBER].MPER,
                            TIMER_A_CAPTURECOMPARE_REGISTER_4,
                            TIMER_A_OUTPUTMODE_RESET_SET,
                            MOT[MOT_NUMBER].MDUT);
                } else
                    MOTOR_stop(MOT_NUMBER);
                PJDIR |= BIT2+BIT3; //GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN2 | GPIO_PIN3);
                P1SEL |= BIT5; //GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN5);
                GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN7);
                break;
            default:;
        }
    }
}

/*
void MOTOR_rotationBackward(uint8_t MOT_NUMBER)
{
    MOT[MOT_NUMBER].MOT_DIR = BACKWARD;
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
            break;
        case MOTOR2:
            GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
            break;
        case MOTOR3:
            GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN1);
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0);
            break;
        case MOTOR4:
            GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN3);
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2);
            break;
        default:;
    }
}
*/

/*
void MOTOR_rotationForward(uint8_t MOT_NUMBER)
{
    MOT[MOT_NUMBER].MOT_DIR = FORWARD;
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5);
            break;
        case MOTOR2:
            GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
            break;
        case MOTOR3:
            GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN1);
            break;
        case MOTOR4:
            GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN3);
            break;
        default:;
    }
}
*/

void MOTOR_disableController(uint8_t MOT_NUMBER)
{
    busy_table[MOT_NUMBER]=NNONE;
    MOT[MOT_NUMBER].MOT_EN = DISABLE;
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5);
            GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN2);
            break;
        case MOTOR2:
            GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN1);
            GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN3);
            break;
        case MOTOR3:
            GPIO_setAsInputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1);
            GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN4);
            break;
        case MOTOR4:
            GPIO_setAsInputPin(GPIO_PORT_PJ, GPIO_PIN2 | GPIO_PIN3);
            GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN5);
            break;
        default:;
    }
}


/*
void MOTOR_start(uint8_t MOT_NUMBER)
{
    MOT[MOT_NUMBER].MOT_PWR = ENABLE;
    if (MOT[MOT_NUMBER].MOT_MOD!=CONT_MODE) MOT[MOT_NUMBER].MVAL = 0;
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            TIMER_A_generatePWM(TIMER_A0_BASE,
                    TIMER_A_CLOCKSOURCE_SMCLK,
                    TIMER_A_CLOCKSOURCE_DIVIDER_1,
                    MOT[MOT_NUMBER].MPER,
                    TIMER_A_CAPTURECOMPARE_REGISTER_1,
                    TIMER_A_OUTPUTMODE_RESET_SET,
                    MOT[MOT_NUMBER].MDUT);
            break;
        case MOTOR2:
            TIMER_A_generatePWM(TIMER_A0_BASE,
                    TIMER_A_CLOCKSOURCE_SMCLK,
                    TIMER_A_CLOCKSOURCE_DIVIDER_1,
                    MOT[MOT_NUMBER].MPER,
                    TIMER_A_CAPTURECOMPARE_REGISTER_2,
                    TIMER_A_OUTPUTMODE_RESET_SET,
                    MOT[MOT_NUMBER].MDUT);
            break;
        case MOTOR3:
            TIMER_A_generatePWM(TIMER_A0_BASE,
                    TIMER_A_CLOCKSOURCE_SMCLK,
                    TIMER_A_CLOCKSOURCE_DIVIDER_1,
                    MOT[MOT_NUMBER].MPER,
                    TIMER_A_CAPTURECOMPARE_REGISTER_3,
                    TIMER_A_OUTPUTMODE_RESET_SET,
                    MOT[MOT_NUMBER].MDUT);
            break;
        case MOTOR4:
            TIMER_A_generatePWM(TIMER_A0_BASE,
                    TIMER_A_CLOCKSOURCE_SMCLK,
                    TIMER_A_CLOCKSOURCE_DIVIDER_1,
                    MOT[MOT_NUMBER].MPER,
                    TIMER_A_CAPTURECOMPARE_REGISTER_4,
                    TIMER_A_OUTPUTMODE_RESET_SET,
                    MOT[MOT_NUMBER].MDUT);
            break;
        default:;
    }
}
*/

/*
void MOTOR_fastBrake(uint8_t MOT_NUMBER)
{
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5);
            break;
        case MOTOR2:
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
            break;
        case MOTOR3:
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN1);
            break;
        case MOTOR4:
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2);
            GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN3);
            break;
        default:;
    }
}
*/

void MOTOR_stop(uint8_t MOT_NUMBER)
{
    switch (MOT_NUMBER)
    {
        case MOTOR1:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4|GPIO_PIN5);
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_1,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        MOT[MOT_NUMBER].MPER-1);
            }
            else
            {
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_1,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        0x0001);
            }
            break;
        case MOTOR2:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1);
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_2,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        MOT[MOT_NUMBER].MPER-1);
            }
            else
            {
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_2,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        0x0001);
            }
            break;
        case MOTOR3:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0|GPIO_PIN1);
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_3,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        MOT[MOT_NUMBER].MPER-1);
            }
            else
            {
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_3,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        0x0001);
            }
            break;
        case MOTOR4:
            if (MOT[MOT_NUMBER].MOT_BRK==ENABLE)
            {
                GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2|GPIO_PIN3);
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_4,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        MOT[MOT_NUMBER].MPER-1);
            }
            else
            {
                TIMER_A_generatePWM(TIMER_A0_BASE,
                        TIMER_A_CLOCKSOURCE_SMCLK,
                        TIMER_A_CLOCKSOURCE_DIVIDER_1,
                        MOT[MOT_NUMBER].MPER,
                        TIMER_A_CAPTURECOMPARE_REGISTER_4,
                        TIMER_A_OUTPUTMODE_RESET_SET,
                        0x0001);
            }
            break;
        default:;
    }
    MOT[MOT_NUMBER].MOT_PWR = DISABLE;
    MOT[MOT_NUMBER].MOT_MOD = CONT_MODE;
}


//Handler
void MOTOR_hadler(uint8_t MOT_NUMBER)
{
    //Continues/single mode
    if (MOT[MOT_NUMBER].MCTL & 0x4000)
    {
        if (MOT[MOT_NUMBER].MCTL & 0x2000)
            MOT[MOT_NUMBER].MOT_MOD = ANGLE_MODE;
        else
            MOT[MOT_NUMBER].MOT_MOD = TIME_MODE;
    }
    else
        MOT[MOT_NUMBER].MOT_MOD = CONT_MODE;
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
    if (MOT[MOT_NUMBER].MCTL & 0x8000)
        MOTOR_enableController(MOT_NUMBER);
    else
        MOTOR_disableController(MOT_NUMBER);

    MOT[MOT_NUMBER].MSTA = MOT_NO_ERROR;
}
