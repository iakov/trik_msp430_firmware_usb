/*
 * trik_encoder.c
 *
 *  Created on: November 7, 2014 ã.
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_devices.h"
#include "trik_encoder.h"
#include "driverlib.h"

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(PORT1_VECTOR)))
#endif
void PORT1_ISR(void)
{
    if ((GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN0)) && (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN4)))
    {
            /*sprintf(newString,"Right2, CNT=%x\r\n",enc_counter2);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter2++;
            ENC[ENCODER2-ENCODER1].EVAL++;
    }

    if ((GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN6)) && (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1)))
    {
            /*sprintf(newString,"Right3, CNT=%x\r\n",enc_counter3);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter3++;
            ENC[ENCODER3-ENCODER1].EVAL++;
    }

    GPIO_clearInterruptFlag(GPIO_PORT_P1,GPIO_PIN0|GPIO_PIN6);
}




#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(PORT2_VECTOR)))
#endif
void PORT2_ISR(void)
{
    if ((GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN3)) && (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN0)))
    {
            /*sprintf(newString,"Left1, CNT=%x\r\n",enc_counter1);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter1--;
            ENC[ENCODER1-ENCODER1].EVAL--;
    }
    if ((GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN0)) && (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3)))
    {
            /*sprintf(newString,"Right1, CNT=%x\r\n",enc_counter1);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter1++;
            ENC[ENCODER1-ENCODER1].EVAL++;
    }

    if ((GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN4)) && (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN0)))
    {
            /*sprintf(newString,"Left2, CNT=%x\r\n",enc_counter2);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter2--;
            ENC[ENCODER2-ENCODER1].EVAL--;
    }

    if ((GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN1)) && (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN6)))
    {
            /*sprintf(newString,"Left3, CNT=%x\r\n",enc_counter3);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter3--;
            ENC[ENCODER3-ENCODER1].EVAL--;
    }

    if ((GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN5)) && (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN2)))
    {
            /*sprintf(newString,"Left4, CNT=%x\r\n",enc_counter4);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter4--;
            ENC[ENCODER4-ENCODER1].EVAL--;
    }
    if ((GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN2)) && (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5)))
    {
            /*sprintf(newString,"Right4, CNT=%x\r\n",enc_counter4);
            if (cdcSendDataInBackground((uint8_t*)newString,
                    strlen(newString),CDC0_INTFNUM,1))
            {  // Send message to other App
                SendError = 0x01;                          // Something went wrong -- exit
            }*/
            //enc_counter4++;
            ENC[ENCODER4-ENCODER1].EVAL++;
    }

    GPIO_clearInterruptFlag(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5);
}


