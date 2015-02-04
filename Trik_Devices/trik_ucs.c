/*
 * trik_ucs.c
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#include <assert.h>
#include <stdint.h>
#include <msp430f5510.h>
#include "trik_ucs.h"
#include "trik_regaccess.h"

void _UCS_clearFaultFlag(uint8_t mask)
{
        assert(mask <= UCS_XT2OFFG );
        HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~mask;
}

void _SFR_clearInterrupt(uint8_t interruptFlagMask)
{
        HWREG8(SFR_BASE + OFS_SFRIFG1_L) &= ~(interruptFlagMask);
}

