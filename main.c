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

#include <assert.h>

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

// Global flags set by events
volatile uint8_t bDataReceived_event0 = FALSE; // Indicates data has been rx'ed
volatile uint8_t bDataReceived_event1 = FALSE; // without an open rx operation,
                                            // on respective HID0/1 interfaces
#define MAX_STR_LENGTH 32
char wholeString[MAX_STR_LENGTH] = "";
char newString[MAX_STR_LENGTH] = "";
char tmpString[MAX_STR_LENGTH] = "";
char pieceOfString[MAX_STR_LENGTH] = "";

volatile uint8_t n_error = 0;
volatile uint8_t ReceiveError = 0, SendError = 0;

volatile uint32_t timerb_cnt = 0; //Timer B counter 1
volatile uint32_t timerb_ts = 0; //Timer B counter 2

float kx, ky, xx, yy; //Temp vars

//Copied from driverlib wdt_a.c
#define OFS_WDTCTL             (0x000C)       /* Watchdog Timer Control */
#define OFS_WDTCTL_L           OFS_WDTCTL
#define HWREG8(x)                                                             \
        (*((volatile uint8_t*)((uint16_t)x)))
#define HWREG16(x)                                                             \
        (*((volatile uint16_t*)((uint16_t)x)))


void _WDT_A_hold(uint32_t baseAddress)
{
        //Set Hold bit
        uint8_t newWDTStatus = ( HWREG8(baseAddress + OFS_WDTCTL_L) | WDTHOLD );

        HWREG16(baseAddress + OFS_WDTCTL) = WDTPW + newWDTStatus;
}

//Copied from driverlib pmm.c
#define PMM_CORE_LEVEL_0                                             PMMCOREV_0
#define PMM_CORE_LEVEL_1                                             PMMCOREV_1
#define PMM_CORE_LEVEL_2                                             PMMCOREV_2
#define PMM_CORE_LEVEL_3                                             PMMCOREV_3
#define bool   _Bool
#define STATUS_FAIL     0x00
#define STATUS_SUCCESS  0x01
#define OFS_PMMCTL0            (0x0000)       /* PMM Control 0 */
#define OFS_PMMCTL0_L          OFS_PMMCTL0
#define OFS_PMMCTL0_H          OFS_PMMCTL0+1
#define OFS_PMMRIE             (0x000E)       /* PMM and RESET Interrupt Enable */
#define OFS_SVSMHCTL           (0x0004)       /* SVS and SVM high side control register */
#define OFS_SVSMLCTL           (0x0006)       /* SVS and SVM low side control register */
#define OFS_PMMIFG             (0x000C)       /* PMM Interrupt Flag */

uint16_t _PMM_setVCoreUp( uint8_t level)
{
        uint32_t PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;

        //The code flow for increasing the Vcore has been altered to work around
        //the erratum FLASH37.
        //Please refer to the Errata sheet to know if a specific device is affected
        //DO NOT ALTER THIS FUNCTION

        //Open PMM registers for write access
        HWREG8(PMM_BASE + OFS_PMMCTL0_H) = 0xA5;

        //Disable dedicated Interrupts
        //Backup all registers
        PMMRIE_backup = HWREG16(PMM_BASE + OFS_PMMRIE);
        HWREG16(PMM_BASE + OFS_PMMRIE) &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE |
                                            SVSLPE | SVMHVLRIE | SVMHIE |
                                            SVSMHDLYIE | SVMLVLRIE | SVMLIE |
                                            SVSMLDLYIE
                                            );
        SVSMHCTL_backup = HWREG16(PMM_BASE + OFS_SVSMHCTL);
        SVSMLCTL_backup = HWREG16(PMM_BASE + OFS_SVSMLCTL);

        //Clear flags
        HWREG16(PMM_BASE + OFS_PMMIFG) = 0;

        //Set SVM highside to new level and check if a VCore increase is possible
        HWREG16(PMM_BASE + OFS_SVSMHCTL) = SVMHE | SVSHE | (SVSMHRRL0 * level);

        //Wait until SVM highside is settled
        while ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMHDLYIFG) == 0) ;

        //Clear flag
        HWREG16(PMM_BASE + OFS_PMMIFG) &= ~SVSMHDLYIFG;

        //Check if a VCore increase is possible
        if ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVMHIFG) == SVMHIFG) {
                //-> Vcc is too low for a Vcore increase
                //recover the previous settings
                HWREG16(PMM_BASE + OFS_PMMIFG) &= ~SVSMHDLYIFG;
                HWREG16(PMM_BASE + OFS_SVSMHCTL) = SVSMHCTL_backup;

                //Wait until SVM highside is settled
                while ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMHDLYIFG) == 0) ;

                //Clear all Flags
                HWREG16(PMM_BASE +
                        OFS_PMMIFG) &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                                         SVMLVLRIFG | SVMLIFG |
                                         SVSMLDLYIFG
                                         );

                //Restore PMM interrupt enable register
                HWREG16(PMM_BASE + OFS_PMMRIE) = PMMRIE_backup;
                //Lock PMM registers for write access
                HWREG8(PMM_BASE + OFS_PMMCTL0_H) = 0x00;
                //return: voltage not set
                return STATUS_FAIL;
        }

        //Set also SVS highside to new level
        //Vcc is high enough for a Vcore increase
        HWREG16(PMM_BASE + OFS_SVSMHCTL) |= (SVSHRVL0 * level);

        //Wait until SVM highside is settled
        while ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMHDLYIFG) == 0) ;

        //Clear flag
        HWREG16(PMM_BASE + OFS_PMMIFG) &= ~SVSMHDLYIFG;

        //Set VCore to new level
        HWREG8(PMM_BASE + OFS_PMMCTL0_L) = PMMCOREV0 * level;

        //Set SVM, SVS low side to new level
        HWREG16(PMM_BASE + OFS_SVSMLCTL) = SVMLE | (SVSMLRRL0 * level) |
                                           SVSLE | (SVSLRVL0 * level);

        //Wait until SVM, SVS low side is settled
        while ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMLDLYIFG) == 0) ;

        //Clear flag
        HWREG16(PMM_BASE + OFS_PMMIFG) &= ~SVSMLDLYIFG;
        //SVS, SVM core and high side are now set to protect for the new core level

        //Restore Low side settings
        //Clear all other bits _except_ level settings
        HWREG16(PMM_BASE + OFS_SVSMLCTL) &= (SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 +
                                             SVSMLRRL1 + SVSMLRRL2
                                             );

        //Clear level settings in the backup register,keep all other bits
        SVSMLCTL_backup &=
                ~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

        //Restore low-side SVS monitor settings
        HWREG16(PMM_BASE + OFS_SVSMLCTL) |= SVSMLCTL_backup;

        //Restore High side settings
        //Clear all other bits except level settings
        HWREG16(PMM_BASE + OFS_SVSMHCTL) &= (SVSHRVL0 + SVSHRVL1 +
                                             SVSMHRRL0 + SVSMHRRL1 +
                                             SVSMHRRL2
                                             );

        //Clear level settings in the backup register,keep all other bits
        SVSMHCTL_backup &=
                ~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

        //Restore backup
        HWREG16(PMM_BASE + OFS_SVSMHCTL) |= SVSMHCTL_backup;

        //Wait until high side, low side settled
        while (((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMLDLYIFG) == 0) ||
               ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMHDLYIFG) == 0)) ;

        //Clear all Flags
        HWREG16(PMM_BASE + OFS_PMMIFG) &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                                            SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG
                                            );

        //Restore PMM interrupt enable register
        HWREG16(PMM_BASE + OFS_PMMRIE) = PMMRIE_backup;

        //Lock PMM registers for write access
        HWREG8(PMM_BASE + OFS_PMMCTL0_H) = 0x00;

        return STATUS_SUCCESS;
}

uint16_t _PMM_setVCoreDown( uint8_t level)
{
        uint32_t PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;

        //The code flow for decreasing the Vcore has been altered to work around
        //the erratum FLASH37.
        //Please refer to the Errata sheet to know if a specific device is affected
        //DO NOT ALTER THIS FUNCTION

        //Open PMM registers for write access
        HWREG8(PMM_BASE + OFS_PMMCTL0_H) = 0xA5;

        //Disable dedicated Interrupts
        //Backup all registers
        PMMRIE_backup = HWREG16(PMM_BASE + OFS_PMMRIE);
        HWREG16(PMM_BASE + OFS_PMMRIE) &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE |
                                            SVSLPE | SVMHVLRIE | SVMHIE |
                                            SVSMHDLYIE | SVMLVLRIE | SVMLIE |
                                            SVSMLDLYIE
                                            );
        SVSMHCTL_backup = HWREG16(PMM_BASE + OFS_SVSMHCTL);
        SVSMLCTL_backup = HWREG16(PMM_BASE + OFS_SVSMLCTL);

        //Clear flags
        HWREG16(PMM_BASE + OFS_PMMIFG) &= ~(SVMHIFG | SVSMHDLYIFG |
                                            SVMLIFG | SVSMLDLYIFG
                                            );

        //Set SVM, SVS high & low side to new settings in normal mode
        HWREG16(PMM_BASE + OFS_SVSMHCTL) = SVMHE | (SVSMHRRL0 * level) |
                                           SVSHE | (SVSHRVL0 * level);
        HWREG16(PMM_BASE + OFS_SVSMLCTL) = SVMLE | (SVSMLRRL0 * level) |
                                           SVSLE | (SVSLRVL0 * level);

        //Wait until SVM high side and SVM low side is settled
        while ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMHDLYIFG) == 0 ||
               (HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMLDLYIFG) == 0) ;

        //Clear flags
        HWREG16(PMM_BASE + OFS_PMMIFG) &= ~(SVSMHDLYIFG + SVSMLDLYIFG);
        //SVS, SVM core and high side are now set to protect for the new core level

        //Set VCore to new level
        HWREG8(PMM_BASE + OFS_PMMCTL0_L) = PMMCOREV0 * level;

        //Restore Low side settings
        //Clear all other bits _except_ level settings
        HWREG16(PMM_BASE + OFS_SVSMLCTL) &= (SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 +
                                             SVSMLRRL1 + SVSMLRRL2
                                             );

        //Clear level settings in the backup register,keep all other bits
        SVSMLCTL_backup &=
                ~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

        //Restore low-side SVS monitor settings
        HWREG16(PMM_BASE + OFS_SVSMLCTL) |= SVSMLCTL_backup;

        //Restore High side settings
        //Clear all other bits except level settings
        HWREG16(PMM_BASE + OFS_SVSMHCTL) &= (SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 +
                                             SVSMHRRL1 + SVSMHRRL2
                                             );

        //Clear level settings in the backup register, keep all other bits
        SVSMHCTL_backup &=
                ~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

        //Restore backup
        HWREG16(PMM_BASE + OFS_SVSMHCTL) |= SVSMHCTL_backup;

        //Wait until high side, low side settled
        while (((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMLDLYIFG) == 0) ||
               ((HWREG16(PMM_BASE + OFS_PMMIFG) & SVSMHDLYIFG) == 0)) ;

        //Clear all Flags
        HWREG16(PMM_BASE + OFS_PMMIFG) &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                                            SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG
                                            );

        //Restore PMM interrupt enable register
        HWREG16(PMM_BASE + OFS_PMMRIE) = PMMRIE_backup;
        //Lock PMM registers for write access
        HWREG8(PMM_BASE + OFS_PMMCTL0_H) = 0x00;
        //Return: OK
        return STATUS_SUCCESS;
}

bool _PMM_setVCore( uint8_t level)
{
        assert(
                (PMM_CORE_LEVEL_0 == level) ||
                (PMM_CORE_LEVEL_1 == level) ||
                (PMM_CORE_LEVEL_2 == level) ||
                (PMM_CORE_LEVEL_3 == level)
                );

        uint8_t actlevel;
        bool status = STATUS_SUCCESS;

        //Set Mask for Max. level
        level &= PMMCOREV_3;

        //Get actual VCore
        actlevel = (HWREG16(PMM_BASE + OFS_PMMCTL0) & PMMCOREV_3);

        //step by step increase or decrease
        while ((level != actlevel) && (status == STATUS_SUCCESS)) {
                if (level > actlevel)
                        status = _PMM_setVCoreUp(++actlevel);
                else
                        status = _PMM_setVCoreDown(--actlevel);
        }

        return status;
}

//Copied from driverlib ucs.c
#define UCS_XT2OFFG                                                     XT2OFFG
#define OFS_UCSCTL7            (0x000E)       /* UCS Control Register 7 */
#define UCS_DCOFFG                                                       DCOFFG
#define OFS_SFRIFG1            (0x0002)       /* Interrupt Flag 1 */
#define OFS_SFRIFG1_L          OFS_SFRIFG1
#define SFR_OSCILLATOR_FAULT_INTERRUPT                                     OFIE

void _UCS_clearFaultFlag(uint8_t mask
                        )
{
        assert(mask <= UCS_XT2OFFG );
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~mask;
}

void _SFR_clearInterrupt(uint8_t interruptFlagMask)
{
        HWREG8(SFR_BASE + OFS_SFRIFG1_L) &= ~(interruptFlagMask);
}


/*  
 * ======== main ========
 */
void main (void)
{
    _WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    // MSP430 USB requires the maximum Vcore setting; do not modify
#ifndef DRIVERLIB_LEGACY_MODE
    _PMM_setVCore(PMM_CORE_LEVEL_2);

#else
    //PMM_setVCore(PMM_BASE, PMM_CORE_LEVEL_2);
#endif

    initPorts();           // Config GPIOS for low-power (output low)
    initClocks(24000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    USB_setup(TRUE,TRUE);  // Init USB & events; if a host is present, connect

    initGlobalVars(); //Init variables and structires
    initReferenceTemperature(); //Init ref and temp sensor
    initADC10(); //Init ADC
    initPBPorts(); //Init B ports

    //Enable async timer
    ASYNCTMR.ATCTL |= AT_EN;
    ASYNCTIMER_handler();

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
                        n_error = PROTOCOL_handler(wholeString,newString); //Protocol handler
                        memset(wholeString,0,MAX_STR_LENGTH);   // Clear wholeString
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
                    //strncat(wholeString,pieceOfString,strlen(pieceOfString));
                    //memset(wholeString,0,MAX_STR_LENGTH);   // Clear wholeString
                    memset(pieceOfString,0,MAX_STR_LENGTH);   // Clear wholeString
                }


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
            _UCS_clearFaultFlag(UCS_XT2OFFG);
            _UCS_clearFaultFlag(UCS_DCOFFG);
            _SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

#else
            //UCS_clearFaultFlag(UCS_BASE, UCS_XT2OFFG);
            //UCS_clearFaultFlag(UCS_BASE, UCS_DCOFFG);
            //SFR_clearInterrupt(SFR_BASE, SFR_OSCILLATOR_FAULT_INTERRUPT);
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

        //For async output data
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
                PROTOCOL_recvResponse(tmpString,nnn,0x05,EEVAL,ENC[nnn-ENCODER1].EVAL);
                if (cdcSendDataInBackground((uint8_t*)tmpString,strlen(tmpString),CDC1_INTFNUM,1))
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
                PROTOCOL_recvResponse(tmpString,nnn,0x05,SSVAL,SENS[nnn-SENSOR1].SVAL);
                if (cdcSendDataInBackground((uint8_t*)tmpString,strlen(tmpString),CDC1_INTFNUM,1))
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

        //For touch read event
        timerb_ts++;
        if (timerb_ts > 384)
        {
            if (isTouched())
            {
                TOUCH.CURX = touchReadX();
                TOUCH.CURY = touchReadY();

                //Calibration routine
                if (TOUCH.TMOD)
                {
                    if (TOUCH.CURX < TOUCH.MINX) TOUCH.MINX = TOUCH.CURX;
                    if (TOUCH.CURY < TOUCH.MINY) TOUCH.MINY = TOUCH.CURY;
                    if (TOUCH.CURX > TOUCH.MAXX) TOUCH.MAXX = TOUCH.CURX;
                    if (TOUCH.CURY > TOUCH.MAXY) TOUCH.MAXY = TOUCH.CURY;
                }

                kx = (float)TOUCH.SCRX / (float)(TOUCH.MAXX - TOUCH.MINX);
                ky = (float)TOUCH.SCRY / (float)(TOUCH.MAXY - TOUCH.MINY);

                xx = (float)TOUCH.SCRX - (float)(TOUCH.CURX - TOUCH.MINX) * kx;
                yy = (float)(TOUCH.CURY - TOUCH.MINY) * ky;

                mouseReport.lx = (uint8_t)((uint16_t)xx & 0xFF);
                mouseReport.hx = (uint8_t)(((uint16_t)xx >> 8) & 0xFF);
                mouseReport.ly = (uint8_t)((uint16_t)yy & 0xFF);
                mouseReport.hy = (uint8_t)(((uint16_t)yy >> 8) & 0xFF);

                mouseReport.buttons = 1 - mouseReport.buttons;

                USBHID_sendReport((void *)&mouseReport, HID0_INTFNUM);
            }
            timerb_ts = 0;
        }

        break;
    default:
        break;
    }

    TB0CTL &= ~TBIFG; //TIMER_B_clearTimerInterruptFlag(TIMER_B0_BASE);
}

//Released_Version_4_10_02
