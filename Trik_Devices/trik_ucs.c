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

bool _UCS_bypassXT2WithTimeout(uint16_t timeout)
{
        assert(timeout > 0);

        //Switch off XT2 oscillator and enable BYPASS mode
        HWREG16(UCS_BASE + OFS_UCSCTL6) |= (XT2BYPASS + XT2OFF );

        do {
                //Clear OSC flaut Flags
                HWREG8(UCS_BASE + OFS_UCSCTL7) &= ~(XT2OFFG);

#if defined (__CC430F5133__) || (__CC430F5135__) || (__CC430F5137__) || \
                (__CC430F6125__) || (__CC430F6126__) || (__CC430F6127__) || \
                (__CC430F6135__) || (__CC430F6137__) || (__CC430F5123__) || \
                (__CC430F5125__) || (__CC430F5143__) || (__CC430F5145__) || \
                (__CC430F5147__) || (__CC430F6143__) || (__CC430F6145__) || \
                (__CC430F6147__)
                // CC430 uses a different fault mechanism. It requires 3 VLO clock
                // cycles delay.If 20MHz CPU, 5000 clock cycles are required in worst
                // case.
                __delay_cycles(5000);
#endif

                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
        } while ((HWREG8(UCS_BASE + OFS_UCSCTL7) & XT2OFFG) && --timeout);

        if (timeout)
                return STATUS_SUCCESS;
        else
                return STATUS_FAIL;
}

