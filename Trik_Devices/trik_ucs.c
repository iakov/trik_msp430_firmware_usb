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

void _UCS_clockSignalInit(uint8_t selectedClockSignal,
                         uint16_t clockSource,
                         uint16_t clockSourceDivider
                         )
{
        assert(
                (UCS_XT1CLK_SELECT == clockSource) ||
                (UCS_VLOCLK_SELECT == clockSource) ||
                (UCS_REFOCLK_SELECT == clockSource) ||
                (UCS_DCOCLK_SELECT == clockSource) ||
                (UCS_DCOCLKDIV_SELECT == clockSource) ||
                (UCS_XT2CLK_SELECT == clockSource)
                );

        assert(
                (UCS_CLOCK_DIVIDER_1 == clockSourceDivider) ||
                (UCS_CLOCK_DIVIDER_2 == clockSourceDivider) ||
                (UCS_CLOCK_DIVIDER_4 == clockSourceDivider) ||
                (UCS_CLOCK_DIVIDER_8 == clockSourceDivider) ||
                (UCS_CLOCK_DIVIDER_16 == clockSourceDivider) ||
                (UCS_CLOCK_DIVIDER_32 == clockSourceDivider)
                );

        switch (selectedClockSignal) {
        case UCS_ACLK:
                HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELA_7);
                clockSource = clockSource << 8;
                HWREG16(UCS_BASE + OFS_UCSCTL4) |= (clockSource);

                HWREG16(UCS_BASE + OFS_UCSCTL5) &= ~(DIVA_7);
                clockSourceDivider = clockSourceDivider << 8;
                HWREG16(UCS_BASE + OFS_UCSCTL5) |= clockSourceDivider;
                break;
        case UCS_SMCLK:
                HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELS_7);
                clockSource = clockSource << 4;
                HWREG16(UCS_BASE + OFS_UCSCTL4) |= (clockSource);

                HWREG16(UCS_BASE + OFS_UCSCTL5) &= ~(DIVS_7);
                clockSourceDivider = clockSourceDivider << 4;
                HWREG16(UCS_BASE + OFS_UCSCTL5) |= clockSourceDivider;
                break;
        case UCS_MCLK:
                HWREG16(UCS_BASE + OFS_UCSCTL4) &= ~(SELM_7);
                HWREG16(UCS_BASE + OFS_UCSCTL4) |= (clockSource);

                HWREG16(UCS_BASE + OFS_UCSCTL5) &= ~(DIVM_7);
                HWREG16(UCS_BASE + OFS_UCSCTL5) |= clockSourceDivider;
                break;
        case UCS_FLLREF:
                assert(clockSource <= SELA_5);
                HWREG8(UCS_BASE + OFS_UCSCTL3) &=  ~(SELREF_7);

                clockSource = clockSource << 4;
                HWREG8(UCS_BASE + OFS_UCSCTL3) |= (clockSource);

                HWREG8(UCS_BASE + OFS_UCSCTL3) &= ~(FLLREFDIV_7);
                //Note that dividers for FLLREF are slightly different
                //Hence handled differently from other CLK signals
                switch (clockSourceDivider) {
                case UCS_CLOCK_DIVIDER_12:
                        HWREG8(UCS_BASE + OFS_UCSCTL3) |= FLLREFDIV__12;
                        break;
                case UCS_CLOCK_DIVIDER_16:
                        HWREG8(UCS_BASE + OFS_UCSCTL3) |= FLLREFDIV__16;
                        break;
                default:
                        HWREG8(UCS_BASE + OFS_UCSCTL3) |= clockSourceDivider;
                        break;
                }

                break;
        }
}

void _UCS_initFLL(uint16_t fsystem,
                 uint16_t ratio
                 )
{
        uint16_t d, dco_div_bits;
        uint16_t mode = 0;

        //Save actual state of FLL loop control, then disable it. This is needed to
        //prevent the FLL from acting as we are making fundamental modifications to
        //the clock setup.
        uint16_t srRegisterState = __get_SR_register() & SCG0;

        d = ratio;
        //Have at least a divider of 2
        dco_div_bits = FLLD__2;

        if (fsystem > 16000) {
                d >>= 1;
                mode = 1;
        } else
                //fsystem = fsystem * 2
                fsystem <<= 1;

        while (d > 512) {
                //Set next higher div level
                dco_div_bits = dco_div_bits + FLLD0;
                d >>= 1;
        }

        // Disable FLL
        __bis_SR_register(SCG0);

        //Set DCO to lowest Tap
        HWREG8(UCS_BASE + OFS_UCSCTL0_H) = 0x0000;

        //Reset FN bits
        HWREG16(UCS_BASE + OFS_UCSCTL2) &= ~(0x03FF);
        HWREG16(UCS_BASE + OFS_UCSCTL2) = dco_div_bits | (d - 1);

        if (fsystem <= 630)             //fsystem < 0.63MHz
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_0;
        else if (fsystem <  1250)       //0.63MHz < fsystem < 1.25MHz
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_1;
        else if (fsystem <  2500)       //1.25MHz < fsystem <  2.5MHz
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_2;
        else if (fsystem <  5000)       //2.5MHz  < fsystem <    5MHz
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_3;
        else if (fsystem <  10000)      //5MHz    < fsystem <   10MHz
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_4;
        else if (fsystem <  20000)      //10MHz   < fsystem <   20MHz
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_5;
        else if (fsystem <  40000)      //20MHz   < fsystem <   40MHz
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_6;
        else
                HWREG8(UCS_BASE + OFS_UCSCTL1) = DCORSEL_7;

        // Re-enable FLL
        __bic_SR_register(SCG0);

        while (HWREG8(UCS_BASE + OFS_UCSCTL7_L) & DCOFFG) {
                //Clear OSC flaut Flags
                HWREG8(UCS_BASE + OFS_UCSCTL7_L) &= ~(DCOFFG);

                //Clear OFIFG fault flag
                HWREG8(SFR_BASE + OFS_SFRIFG1) &= ~OFIFG;
        }

        // Restore previous SCG0
        __bis_SR_register(srRegisterState);

        if (mode == 1) {
                //fsystem > 16000
                //Select DCOCLK
                HWREG16(UCS_BASE + OFS_UCSCTL4) &=  ~(SELM_7 + SELS_7);
                HWREG16(UCS_BASE + OFS_UCSCTL4) |= SELM__DCOCLK + SELS__DCOCLK;
        } else {
                //Select DCODIVCLK
                HWREG16(UCS_BASE + OFS_UCSCTL4) &=  ~(SELM_7 + SELS_7);
                HWREG16(UCS_BASE + OFS_UCSCTL4) |= SELM__DCOCLKDIV + SELS__DCOCLKDIV;
        }

}

void _UCS_initFLLSettle(uint16_t fsystem,
                       uint16_t ratio
                       )
{
        volatile uint16_t x = ratio * 32;

        _UCS_initFLL(fsystem, ratio);

        while (x--)
                __delay_cycles(30);
}

void _UCS_XT2Off(void)
{
        //Switch off XT2 oscillator
        HWREG16(UCS_BASE + OFS_UCSCTL6) |= XT2OFF;
}
