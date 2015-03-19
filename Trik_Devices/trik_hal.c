/*
 * trik_hal.c
 *
 *  Imported from driverlib: Fabruary 4, 2015
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_ucs.h"
#include "trik_hal.h"

/*
* This function drives all the I/O's as output-low, to avoid floating inputs
* (which cause extra power to be consumed).  This setting is compatible with
 * TI FET target boards, the F5529 Launchpad, and F5529 Experimenters Board;
 * but may not be compatible with custom hardware, which may have components
 * attached to the I/Os that could be affected by these settings.  So if using
* other boards, this function may need to be modified.
*/

void _initPorts(void)
{
#ifdef __MSP430_HAS_PORT1_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_ALL);
    P1DIR &= ~(GPIO_ALL);
    P1OUT &= ~(GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT2_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_ALL);
    P2DIR &= ~(GPIO_ALL);
    P2OUT &= ~(GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT3_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_ALL);
    P3DIR &= ~(GPIO_ALL);
    P3OUT &= ~(GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT4_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_ALL);
    P4DIR &= ~(GPIO_ALL);
    P4OUT &= ~(GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT5_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_ALL);
    P5DIR &= ~(GPIO_ALL);
    P5OUT &= ~(GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT6_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_ALL);
    P6DIR &= ~(GPIO_ALL);
    P6OUT &= ~(GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT7_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT8_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT9_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORTJ_R__
    //GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_ALL);
    //GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_ALL);
    PJDIR &= ~(GPIO_ALL);
    PJOUT &= ~(GPIO_ALL);
#endif
}

/* Configures the system clocks:
* MCLK = SMCLK = DCO/FLL = mclkFreq (expected to be expressed in Hz)
* ACLK = FLLref = REFO=32kHz
*
* XT2 is not configured here.  Instead, the USB API automatically starts XT2
* when beginning USB communication, and optionally disables it during USB
* suspend.  It's left running after the USB host is disconnected, at which
* point you're free to disable it.  You need to configure the XT2 frequency
* in the Descriptor Tool (currently set to 4MHz in this example).
* See the Programmer's Guide for more information.
*/

void _initClocks(uint32_t mclkFreq)
{
#ifndef DRIVERLIB_LEGACY_MODE

    _UCS_clockSignalInit(
       UCS_FLLREF,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    _UCS_clockSignalInit(
       UCS_ACLK,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    _UCS_initFLLSettle(
        mclkFreq/1000,
        mclkFreq/32768);

#else
    /*
    UCS_clockSignalInit(
       UCS_BASE,
       UCS_FLLREF,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    UCS_clockSignalInit(
       UCS_BASE,
       UCS_ACLK,
       UCS_REFOCLK_SELECT,
       UCS_CLOCK_DIVIDER_1);

    UCS_initFLLSettle(
        UCS_BASE,
        mclkFreq/1000,
        mclkFreq/32768);
     */
#endif

}


