/*
 * trick_bsl.c
 *
 *  Created on: 27 окт. 2014 г.
 *      Author: Rostislav Varzar
 */

#include "trik_bsl.h"

//Enter to BSL
uint8_t BSL_enterBSL(uint32_t bslpswd)
{
    if (bslpswd == 0xA480E917)
    {
        USB_disable();
        __disable_interrupt();
        ((void (*)())0x1000)();
        return PSWD_OK;
    }
    else
        return PSWD_FAIL;
}

