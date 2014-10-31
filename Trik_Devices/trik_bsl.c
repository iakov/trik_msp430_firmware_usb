/*
 * trick_bsl.c
 *
 *  Created on: October 27, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_devices.h"
#include "trik_bsl.h"
#include "USB_API/USB_Common/usb.h"


//Enter to BSL
uint8_t BSL_enterBSL(uint32_t bslpswd)
{
    if (bslpswd == 0xA480E917)
    {
        TIMER_B_stop(TIMER_B0_BASE);
        TIMER_B_disableInterrupt(TIMER_B0_BASE);
        __disable_interrupt();
        USB_disable();
        ((void (*)())0x1000)();
        return PSWD_OK;
    }
    else
        return PSWD_FAIL;
}

