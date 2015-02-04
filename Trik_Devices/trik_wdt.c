/*
 * trik_wdt.c
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#include <assert.h>
#include <stdint.h>
#include <msp430f5510.h>
#include "trik_wdt.h"
#include "trik_regaccess.h"

void _WDT_A_hold(uint32_t baseAddress)
{
        //Set Hold bit
        uint8_t newWDTStatus = ( HWREG8(baseAddress + OFS_WDTCTL_L) | WDTHOLD );

        HWREG16(baseAddress + OFS_WDTCTL) = WDTPW + newWDTStatus;
}
