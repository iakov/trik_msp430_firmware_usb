/*
 * trik_pmm.h
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_PMM_H_
#define TRIK_PMM_H_

#define PMM_CORE_LEVEL_0                                             PMMCOREV_0
#define PMM_CORE_LEVEL_1                                             PMMCOREV_1
#define PMM_CORE_LEVEL_2                                             PMMCOREV_2
#define PMM_CORE_LEVEL_3                                             PMMCOREV_3
#define bool   _Bool
#define STATUS_FAIL     0x00
#define STATUS_SUCCESS  0x01
#define OFS_PMMCTL0            (0x0000)       /* PMM Control 0 */
#define OFS_PMMCTL0_L          OFS_PMMCTL0
#define OFS_PMMCTL0_H          OFS_PMMCTL0+1
#define OFS_PMMRIE             (0x000E)       /* PMM and RESET Interrupt Enable */
#define OFS_SVSMHCTL           (0x0004)       /* SVS and SVM high side control register */
#define OFS_SVSMLCTL           (0x0006)       /* SVS and SVM low side control register */
#define OFS_PMMIFG             (0x000C)       /* PMM Interrupt Flag */

uint16_t _PMM_setVCoreUp( uint8_t level);
uint16_t _PMM_setVCoreDown( uint8_t level);
bool _PMM_setVCore( uint8_t level);

#endif /* TRIK_PMM_H_ */
