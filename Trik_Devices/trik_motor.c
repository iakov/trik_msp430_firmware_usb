/*
 * Trik_Motor.c
 *
 *  Created on: 21 окт. 2014 г.
 *      Author: Rostislav Varzar
 */

#include "trik_motor.h"



//API functions
void MOTOR_enableController(uint8_t MOT_NUMBER)
{
    //Busy table
    if (busy_table[MOT_NUMBER]==NNONE)
    {
        busy_table[MOT_NUMBER]=MOT_NUMBER;
        //Configure GPIO ports
        switch (MOT_NUMBER)
        {
            case MOTOR1:
                GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5);
                GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5);
                GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN2);
                if (MOT[MOT_NUMBER].MCTL & 0x04)
                    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2);
                else
                    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN2);
                GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN1);
                break;
            case MOTOR2:
                GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN0);
                GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN1);
                GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN3);
                if (MOT[MOT_NUMBER].MCTL & 0x04)
                    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3);
                else
                    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN3);
                GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN6);
                break;
            case MOTOR3:
                GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1);
                GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1);
                GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN4);
                if (MOT[MOT_NUMBER].MCTL & 0x04)
                    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN4);
                else
                    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN4);
                GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN7);
                break;
            case MOTOR4:
                GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN2 | GPIO_PIN3);
                GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN2 | GPIO_PIN3);
                GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);
                if (MOT[MOT_NUMBER].MCTL & 0x04)
                    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN5);
                else
                    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);
                GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN7);
                break;
            default:;
        }
    }
}

void MOTOR_disableController(uint8_t MOT_NUMBER)
{
    busy_table[MOT_NUMBER]=NNONE;
    //Configure GPIO ports
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




//Handler
uint8_t MOTOR_hadler(uint8_t MOT_NUMBER)
{




    return 0x00;
}
