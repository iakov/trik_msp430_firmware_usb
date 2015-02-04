/*
 * trik_ucs.h
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_UCS_H_
#define TRIK_UCS_H_

#define UCS_XT2OFFG                                                     XT2OFFG
#define UCS_DCOFFG                                                       DCOFFG
#define OFS_UCSCTL7            (0x000E)       /* UCS Control Register 7 */
#define OFS_SFRIFG1            (0x0002)       /* Interrupt Flag 1 */
#define OFS_SFRIFG1_L          OFS_SFRIFG1
#define SFR_OSCILLATOR_FAULT_INTERRUPT                                     OFIE

void _UCS_clearFaultFlag(uint8_t mask);
void _SFR_clearInterrupt(uint8_t interruptFlagMask);

#endif /* TRIK_UCS_H_ */
