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
    return 0x00;
}
