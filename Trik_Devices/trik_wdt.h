/*
 * trik_wdt.h
 *
 *  Imported from driverlib: Fabruary 4, 2015
 */

#ifndef TRIK_WDT_H_
#define TRIK_WDT_H_

#define OFS_WDTCTL             (0x000C)       /* Watchdog Timer Control */
#define OFS_WDTCTL_L           OFS_WDTCTL

void _WDT_A_hold(uint32_t baseAddress);

#endif /* TRIK_WDT_H_ */
