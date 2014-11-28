/*
 * trik_port.c
 *
 *  Created on: November 28, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_port.h"
#include "trik_devices.h"
#include "driverlib.h"

//Write to port
void PORT_write(uint8_t PORT_NUMBER, uint8_t REG_ADDRESS, uint8_t REG_VALUE)
{
    switch (PORT_NUMBER)
    {
        case PORT1:
            if (REG_ADDRESS == PIN) P1IN = REG_VALUE;
            if (REG_ADDRESS == POUT) P1OUT = REG_VALUE;
            if (REG_ADDRESS == PDIR) P1DIR = REG_VALUE;
            if (REG_ADDRESS == PREN) P1REN = REG_VALUE;
            if (REG_ADDRESS == PDS) P1DS = REG_VALUE;
            if (REG_ADDRESS == PSEL) P1SEL = REG_VALUE;
            if (REG_ADDRESS == PIE) P1IE = REG_VALUE;
            if (REG_ADDRESS == PIES) P1IES = REG_VALUE;
            if (REG_ADDRESS == PIFG) P1IFG = REG_VALUE;
            break;
        case PORT2:
            if (REG_ADDRESS == PIN) P2IN = REG_VALUE;
            if (REG_ADDRESS == POUT) P2OUT = REG_VALUE;
            if (REG_ADDRESS == PDIR) P2DIR = REG_VALUE;
            if (REG_ADDRESS == PREN) P2REN = REG_VALUE;
            if (REG_ADDRESS == PDS) P2DS = REG_VALUE;
            if (REG_ADDRESS == PSEL) P2SEL = REG_VALUE;
            if (REG_ADDRESS == PIE) P2IE = REG_VALUE;
            if (REG_ADDRESS == PIES) P2IES = REG_VALUE;
            if (REG_ADDRESS == PIFG) P2IFG = REG_VALUE;
            break;
        case PORT3:
            if (REG_ADDRESS == PIN) P3IN = REG_VALUE;
            if (REG_ADDRESS == POUT) P3OUT = REG_VALUE;
            if (REG_ADDRESS == PDIR) P3DIR = REG_VALUE;
            if (REG_ADDRESS == PREN) P3REN = REG_VALUE;
            if (REG_ADDRESS == PDS) P3DS = REG_VALUE;
            if (REG_ADDRESS == PSEL) P3SEL = REG_VALUE;
            break;
        case PORT4:
            if (REG_ADDRESS == PIN) P4IN = REG_VALUE;
            if (REG_ADDRESS == POUT) P4OUT = REG_VALUE;
            if (REG_ADDRESS == PDIR) P4DIR = REG_VALUE;
            if (REG_ADDRESS == PREN) P4REN = REG_VALUE;
            if (REG_ADDRESS == PDS) P4DS = REG_VALUE;
            if (REG_ADDRESS == PSEL) P4SEL = REG_VALUE;
            break;
        case PORT5:
            if (REG_ADDRESS == PIN) P5IN = REG_VALUE;
            if (REG_ADDRESS == POUT) P5OUT = REG_VALUE;
            if (REG_ADDRESS == PDIR) P5DIR = REG_VALUE;
            if (REG_ADDRESS == PREN) P5REN = REG_VALUE;
            if (REG_ADDRESS == PDS) P5DS = REG_VALUE;
            if (REG_ADDRESS == PSEL) P5SEL = REG_VALUE;
            break;
        case PORT6:
            if (REG_ADDRESS == PIN) P6IN = REG_VALUE;
            if (REG_ADDRESS == POUT) P6OUT = REG_VALUE;
            if (REG_ADDRESS == PDIR) P6DIR = REG_VALUE;
            if (REG_ADDRESS == PREN) P6REN = REG_VALUE;
            if (REG_ADDRESS == PDS) P6DS = REG_VALUE;
            if (REG_ADDRESS == PSEL) P6SEL = REG_VALUE;
            break;
        case PORTJ:
            if (REG_ADDRESS == PIN) PJIN = REG_VALUE;
            if (REG_ADDRESS == POUT) PJOUT = REG_VALUE;
            if (REG_ADDRESS == PDIR) PJDIR = REG_VALUE;
            if (REG_ADDRESS == PREN) PJREN = REG_VALUE;
            if (REG_ADDRESS == PDS) PJDS = REG_VALUE;
            break;
        default:
            break;
    }
}

//Read from port
uint8_t PORT_read(uint8_t PORT_NUMBER, uint8_t REG_ADDRESS)
{
    switch (PORT_NUMBER)
    {
        case PORT1:
            if (REG_ADDRESS == PIN) return P1IN;
            if (REG_ADDRESS == POUT) return P1OUT;
            if (REG_ADDRESS == PDIR) return P1DIR;
            if (REG_ADDRESS == PREN) return P1REN;
            if (REG_ADDRESS == PDS) return P1DS;
            if (REG_ADDRESS == PSEL) return P1SEL;
            if (REG_ADDRESS == PIE) return P1IE;
            if (REG_ADDRESS == PIES) return P1IES;
            if (REG_ADDRESS == PIFG) return P1IFG;
            break;
        case PORT2:
            if (REG_ADDRESS == PIN) return P2IN;
            if (REG_ADDRESS == POUT) return P2OUT;
            if (REG_ADDRESS == PDIR) return P2DIR;
            if (REG_ADDRESS == PREN) return P2REN;
            if (REG_ADDRESS == PDS) return P2DS;
            if (REG_ADDRESS == PSEL) return P2SEL;
            if (REG_ADDRESS == PIE) return P2IE;
            if (REG_ADDRESS == PIES) return P2IES;
            if (REG_ADDRESS == PIFG) return P2IFG;
            break;
        case PORT3:
            if (REG_ADDRESS == PIN) return P3IN;
            if (REG_ADDRESS == POUT) return P3OUT;
            if (REG_ADDRESS == PDIR) return P3DIR;
            if (REG_ADDRESS == PREN) return P3REN;
            if (REG_ADDRESS == PDS) return P3DS;
            if (REG_ADDRESS == PSEL) return P3SEL;
            break;
        case PORT4:
            if (REG_ADDRESS == PIN) return P4IN;
            if (REG_ADDRESS == POUT) return P4OUT;
            if (REG_ADDRESS == PDIR) return P4DIR;
            if (REG_ADDRESS == PREN) return P4REN;
            if (REG_ADDRESS == PDS) return P4DS;
            if (REG_ADDRESS == PSEL) return P4SEL;
            break;
        case PORT5:
            if (REG_ADDRESS == PIN) return P5IN;
            if (REG_ADDRESS == POUT) return P5OUT;
            if (REG_ADDRESS == PDIR) return P5DIR;
            if (REG_ADDRESS == PREN) return P5REN;
            if (REG_ADDRESS == PDS) return P5DS;
            if (REG_ADDRESS == PSEL) return P5SEL;
            break;
        case PORT6:
            if (REG_ADDRESS == PIN) return P6IN;
            if (REG_ADDRESS == POUT) return P6OUT;
            if (REG_ADDRESS == PDIR) return P6DIR;
            if (REG_ADDRESS == PREN) return P6REN;
            if (REG_ADDRESS == PDS) return P6DS;
            if (REG_ADDRESS == PSEL) return P6SEL;
            break;
        case PORTJ:
            if (REG_ADDRESS == PIN) return PJIN;
            if (REG_ADDRESS == POUT) return PJOUT;
            if (REG_ADDRESS == PDIR) return PJDIR;
            if (REG_ADDRESS == PREN) return PJREN;
            if (REG_ADDRESS == PDS) return PJDS;
            break;
        default:
            break;
    }
    return 0x00;
}
