/*
 * trik_ucs.h
 *
 *  Imported from driverlib: Fabruary 4, 2015
 */

#ifndef TRIK_UCS_H_
#define TRIK_UCS_H_

#define UCS_XT2OFFG                                                     XT2OFFG
#define UCS_DCOFFG                                                       DCOFFG
#define UCS_ACLK                                                           0x01
#define UCS_MCLK                                                           0x02
#define UCS_SMCLK                                                          0x04
#define UCS_FLLREF                                                         0x08
#define OFS_UCSCTL3            (0x0006)       /* UCS Control Register 3 */
#define OFS_UCSCTL4            (0x0008)       /* UCS Control Register 4 */
#define OFS_UCSCTL5            (0x000A)       /* UCS Control Register 5 */
#define OFS_UCSCTL6            (0x000C)       /* UCS Control Register 6 */
#define OFS_UCSCTL7            (0x000E)       /* UCS Control Register 7 */
#define OFS_SFRIFG1            (0x0002)       /* Interrupt Flag 1 */
#define OFS_SFRIFG1_L          OFS_SFRIFG1
#define SFR_OSCILLATOR_FAULT_INTERRUPT                                     OFIE
#define UCS_CLOCK_DIVIDER_1                                             DIVM__1
#define UCS_CLOCK_DIVIDER_2                                             DIVM__2
#define UCS_CLOCK_DIVIDER_4                                             DIVM__4
#define UCS_CLOCK_DIVIDER_8                                             DIVM__8
#define UCS_CLOCK_DIVIDER_12                                           DIVM__32
#define UCS_CLOCK_DIVIDER_16                                           DIVM__16
#define UCS_CLOCK_DIVIDER_32                                           DIVM__32
#define UCS_XT1CLK_SELECT                                          SELM__XT1CLK
#define UCS_VLOCLK_SELECT                                          SELM__VLOCLK
#define UCS_REFOCLK_SELECT                                        SELM__REFOCLK
#define UCS_DCOCLK_SELECT                                          SELM__DCOCLK
#define UCS_DCOCLKDIV_SELECT                                    SELM__DCOCLKDIV
#define UCS_XT2CLK_SELECT                                          SELM__XT2CLK
#define OFS_UCSCTL0            (0x0000)       /* UCS Control Register 0 */
#define OFS_UCSCTL0_L          OFS_UCSCTL0
#define OFS_UCSCTL0_H          OFS_UCSCTL0+1
#define OFS_UCSCTL1            (0x0002)       /* UCS Control Register 1 */
#define OFS_UCSCTL1_L          OFS_UCSCTL1
#define OFS_UCSCTL1_H          OFS_UCSCTL1+1
#define OFS_UCSCTL2            (0x0004)       /* UCS Control Register 2 */
#define OFS_UCSCTL2_L          OFS_UCSCTL2
#define OFS_UCSCTL2_H          OFS_UCSCTL2+1
#define OFS_UCSCTL7            (0x000E)       /* UCS Control Register 7 */
#define OFS_UCSCTL7_L          OFS_UCSCTL7
#define OFS_UCSCTL7_H          OFS_UCSCTL7+1
#define bool   _Bool
#define false  0
#define true   1

void _UCS_clearFaultFlag(uint8_t mask);
void _SFR_clearInterrupt(uint8_t interruptFlagMask);
bool _UCS_bypassXT2WithTimeout(uint16_t timeout);
void _UCS_clockSignalInit(uint8_t selectedClockSignal,
                         uint16_t clockSource,
                         uint16_t clockSourceDivider
                         );
void _UCS_initFLLSettle(uint16_t fsystem,
                       uint16_t ratio
                       );
void _UCS_initFLL(uint16_t fsystem,
                 uint16_t ratio
                 );
void _UCS_XT2Off(void);



#endif /* TRIK_UCS_H_ */
