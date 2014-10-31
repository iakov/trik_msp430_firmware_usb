/*
 * trick_bsl.c
 *
 *  Created on: October 27, 2014
 *      Author: Rostislav Varzar
 */

#include "trik_bsl.h"

//Enter to BSL
uint8_t BSL_enterBSL(uint32_t bslpswd)
{
    if (bslpswd == 0xA480E917)
    {
        __disable_interrupt();
        USB_disable();
        ((void (*)())0x1000)();
        return PSWD_OK;
    }
    else
        return PSWD_FAIL;
}

