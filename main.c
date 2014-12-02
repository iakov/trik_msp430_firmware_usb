/* --COPYRIGHT--,BSD
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*  
 * ======== main.c ========
 *
 * CDC to CDC Chat Demo:
 *
 * This application shows a composite CDC+CDC device. Two instances of a 
 * terminal application are opened, each opening a COM port associated with a 
 * different CDC interface in this device.
 * The MSP430 application echos data between the two interfaces.  
 *
 * ----------------------------------------------------------------------------+
 * Please refer to the Examples Guide for more details.
 * ---------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                 // USB-specific functions
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "USB_API/USB_HID_API/UsbHid.h"
#include "USB_app/usbConstructs.h"

#include "Trik_Devices/trik_protocolhandler.h"
#include "Trik_Devices/trik_devices.h"
#include "Trik_Devices/trik_motor.h"
#include "Trik_Devices/trik_encoder.h"
#include "Trik_Devices/trik_async.h"
#include "Trik_Devices/trik_sensor.h"
#include "Trik_Devices/trik_touch.h"
/*
 * NOTE: Modify hal.h to select a specific evaluation board and customize for
 * your own board.
 */
#include "hal.h"
#include "driverlib.h"

// Global flags set by events
volatile uint8_t bDataReceived_event0 = FALSE; // Indicates data has been rx'ed
volatile uint8_t bDataReceived_event1 = FALSE; // without an open rx operation,
                                            // on respective HID0/1 interfaces
#define MAX_STR_LENGTH 32
char wholeString[MAX_STR_LENGTH] = "";
char newString[MAX_STR_LENGTH] = "";
char pieceOfString[MAX_STR_LENGTH] = "";

volatile uint8_t n_error = 0;
volatile uint8_t ReceiveError = 0, SendError = 0;

volatile uint32_t timerb_cnt = 0; //Timer B counter

uint16_t t,x,y;

/*
typedef struct {
    uint8_t buttons;
    uint8_t dX;
    uint8_t dY;
    uint8_t dZ;
} MOUSE_REPORT;

MOUSE_REPORT mouseReport = { 0, 0, 0, 0 };

volatile uint8_t sendNewMousePosition = FALSE;  // Flag by which timer tells main loop to send a new report

const int16_t tableSinCosLookUp[93][2];                 // Lookup table for mouse data;
uint8_t index = 1;                                     // Index for lookup table
*/

/*  
 * ======== main ========
 */
void main (void)
{
    WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    // MSP430 USB requires the maximum Vcore setting; do not modify
#ifndef DRIVERLIB_LEGACY_MODE
    PMM_setVCore(PMM_CORE_LEVEL_2);

#else
    PMM_setVCore(PMM_BASE, PMM_CORE_LEVEL_2);
#endif

    initPorts();           // Config GPIOS for low-power (output low)
    initClocks(24000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    USB_setup(TRUE,TRUE);  // Init USB & events; if a host is present, connect

    initGlobalVars(); //Init variables and structires
    initReferenceTemperature(); //Init ref and temp sensor
    initADC10(); //Init ADC
    initPBPorts(); //Init B ports

   __enable_interrupt();  // Enable interrupts globally

    while (1)
    {
        switch (USB_connectionState())
        {
            // This case is executed while your device is enumerated on the
            // USB host
            case ST_ENUM_ACTIVE:

                __bis_SR_register(LPM0_bits + GIE);             // Enter LPM0 until awakened by an event handler
                __no_operation();                               // For debugger

                // Exit LPM because of a data-receive event, and fetch the received data

                //CDC0 events
                if (bDataReceived_event0)
                {
                    bDataReceived_event0 = FALSE;
                    memset(pieceOfString,0,MAX_STR_LENGTH);     // Clear pieceOfString
                    cdcReceiveDataInBuffer((uint8_t*)pieceOfString,
                        MAX_STR_LENGTH,
                        CDC0_INTFNUM);
                    //Test for max length
                    if ((strlen(pieceOfString)+strlen(wholeString))>=MAX_STR_LENGTH)
                    {
                        memset(wholeString,0,MAX_STR_LENGTH);
                        memset(pieceOfString,0,MAX_STR_LENGTH);
                    }
                    strncat(wholeString,pieceOfString,strlen(pieceOfString));
                    //Test for end symbol 0x0A
                    if (retInString(wholeString))
                    {              // Wait for enter key to be pressed
                        //n_error = PROTOCOL_handler(wholeString,newString); //Protocol handler
                        t = isTouched();

                        x = touchReadX();
                        y = touchReadY();



                        sprintf(newString,"%d %d %d\r\n",t,x,y);


                        memset(wholeString,0,MAX_STR_LENGTH);   // Clear wholeString

                        //sprintf(newString,"TestNumber=%x %x %x %x\n",t11,t12,t13,t14);
                        if (cdcSendDataInBackground((uint8_t*)newString,
                                strlen(newString),CDC0_INTFNUM,1))
                        {  // Send message to other App
                            SendError = 0x01;                          // Something went wrong -- exit
                            break;
                        }
                    }
                }

                //CDC1 events
                if (bDataReceived_event1)
                {
                    bDataReceived_event1 = FALSE;               // Clear flag early -- just in case execution breaks below because of
                                                                // an error
                    memset(pieceOfString,0,MAX_STR_LENGTH);     // Clear pieceOfString
                    cdcReceiveDataInBuffer((uint8_t*)pieceOfString,
                        MAX_STR_LENGTH,
                        CDC1_INTFNUM);
                    strncat(wholeString,pieceOfString,strlen(pieceOfString));
                    memset(wholeString,0,MAX_STR_LENGTH);   // Clear wholeString
                }



                /*
                //Mouse test
                if (sendNewMousePosition){

                    // Build the report
                    mouseReport.dX =
                        (tableSinCosLookUp[index][0] -
                         tableSinCosLookUp[index - 1][0]) >> 1;
                    mouseReport.dY =
                        (tableSinCosLookUp[index][1] -
                         tableSinCosLookUp[index - 1][1]) >> 1;

                    // Send the report
                    USBHID_sendReport((void *)&mouseReport, HID0_INTFNUM);

                    if (index++ >= 90)
                    {
                        index = 1;
                    }
                }

*/


                break;
            // These cases are executed while your device is disconnected from
            // the host (meaning, not enumerated); enumerated but suspended
            // by the host, or connected to a powered hub without a USB host
            // present.
            case ST_PHYS_DISCONNECTED:
            case ST_ENUM_SUSPENDED:
            case ST_PHYS_CONNECTED_NOENUM_SUSP:
                __bis_SR_register(LPM3_bits + GIE);
                _NOP();
                break;

            // The default is executed for the momentary state
            // ST_ENUM_IN_PROGRESS.  Usually, this state only last a few
            // seconds.  Be sure not to enter LPM3 in this state; USB
            // communication is taking place here, and therefore the mode must
            // be LPM0 or active-CPU.
            case ST_ENUM_IN_PROGRESS:
            default:
                break;
        }


        if (ReceiveError || SendError){
            // TO DO: User can place code here to handle error
        }

    }  // while(1)
}  // main()


/*  
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG ))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
#ifndef DRIVERLIB_LEGACY_MODE
            UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

#else
            UCS_clearFaultFlag(UCS_BASE, UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_BASE, UCS_DCOFFG);
            SFR_clearInterrupt(SFR_BASE, SFR_OSCILLATOR_FAULT_INTERRUPT);
#endif
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is
            // suspended, a "bus error" can occur.  This generates an NMI.  If
            // USB is automatically disconnecting in your software, set a
            // breakpoint here and see if execution hits it.  See the
            // Programmer's Guide for more information.
            SYSBERRIV = 0; //clear bus error flag
            USB_disable(); //Disable
    }
}


// Timer_B7 Interrupt Vector (TBIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERB1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMERB1_VECTOR)))
#endif
void TIMERB1_ISR(void)
{
    //Any access, read or write, of the TBIV register automatically resets the  highest "pending" interrupt flag.
    switch(__even_in_range(TBIV,14))
    {
    case  0: break;                          // No interrupt
    case  2: break;                          // CCR1 not used
    case  4: break;                          // CCR2 not used
    case  6: break;                          // CCR3 not used
    case  8: break;                          // CCR4 not used
    case 10: break;                          // CCR5 not used
    case 12: break;                          // CCR6 not used
    case 14:                                 // overflow

        ASYNCTMR.ATVAL++;

        timerb_cnt++;

        if (timerb_cnt > ASYNCTMR.ATPER)
        {
            timerb_cnt = 0;
        }

        //Async output for encoder
        for (uint8_t nnn=ENCODER1; nnn<=ENCODER4; nnn++)
        {
            if ((timerb_cnt==nnn) && (ENC[nnn-ENCODER1].ECTL & ENC_ASYNC))
            {
                PROTOCOL_recvResponse(newString,nnn,NO_ERROR,EEVAL,ENC[nnn-ENCODER1].EVAL,REG_32bits);
                if (cdcSendDataInBackground((uint8_t*)newString,strlen(newString),CDC0_INTFNUM,1))
                {
                    SendError = 0x01;
                }
            }
        }

        //Async output for sensor
        for (uint8_t nnn=SENSOR1; nnn<=SENSOR18; nnn++)
        {
            if ((timerb_cnt==nnn) && (SENS[nnn-SENSOR1].SCTL & SENS_ASYNC))
            {
                SENSOR_handler(nnn);
                PROTOCOL_recvResponse(newString,nnn,NO_ERROR,SSVAL,SENS[nnn-SENSOR1].SVAL,REG_32bits);
                if (cdcSendDataInBackground((uint8_t*)newString,strlen(newString),CDC0_INTFNUM,1))
                {
                    SendError = 0x01;
                }
            }
        }

        //Motors timer control
        for (uint8_t MOTNUM=MOTOR1; MOTNUM<=MOTOR4; MOTNUM++)
        {
            if ((MOT[MOTNUM].MCTL & MOT_AUTO) && (!(MOT[MOTNUM].MCTL & MOT_ANGLE)))
            {
                MOT[MOTNUM].MVAL++;
                if ((MOT[MOTNUM].MVAL>MOT[MOTNUM].MTMR))
                {
                    MOTOR_stop(MOTNUM);
                }
            }
        }

        //sendNewMousePosition = TRUE;                 // Set flag telling main loop to send a report

        break;
    default:
        break;
    }

    TB0CTL &= ~TBIFG; //TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
}

/*
// Lookup table for mouse position values.  "const" indicates it will be stored
// in flash.
const int16_t tableSinCosLookUp[93][2] = {
    0,200,
    14,200,
    28,198,
    42,196,
    55,192,
    68,188,
    81,183,
    94,177,
    106,170,
    118,162,
    129,153,
    139,144,
    149,134,
    158,123,
    166,112,
    173,100,
    180,88,
    185,75,
    190,62,
    194,48,
    197,35,
    199,21,
    200,7,
    200,-7,
    199,-21,
    197,-35,
    194,-48,
    190,-62,
    185,-75,
    180,-88,
    173,-100,
    166,-112,
    158,-123,
    149,-134,
    139,-144,
    129,-153,
    118,-162,
    106,-170,
    94,-177,
    81,-183,
    68,-188,
    55,-192,
    42,-196,
    28,-198,
    14,-200,
    0,-200,
    -14,-200,
    -28,-198,
    -42,-196,
    -55,-192,
    -68,-188,
    -81,-183,
    -94,-177,
    -106,-170,
    -118,-162,
    -129,-153,
    -139,-144,
    -149,-134,
    -158,-123,
    -166,-112,
    -173,-100,
    -180,-88,
    -185,-75,
    -190,-62,
    -194,-48,
    -197,-35,
    -199,-21,
    -200,-7,
    -200,7,
    -199,21,
    -197,35,
    -194,48,
    -190,62,
    -185,75,
    -180,88,
    -173,100,
    -166,112,
    -158,123,
    -149,134,
    -139,144,
    -129,153,
    -118,162,
    -106,170,
    -94,177,
    -81,183,
    -68,188,
    -55,192,
    -42,196,
    -28,198,
    -14,200,
    0,200
};

*/
//Released_Version_4_10_02
