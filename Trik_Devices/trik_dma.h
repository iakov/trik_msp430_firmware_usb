/*
 * trik_dma.h
 *
 *  Imported from driverlib: Fabruary 4, 2015
 */

#ifndef TRIK_DMA_H_
#define TRIK_DMA_H_

#define DMA_CHANNEL_7                                                    (0x70)
#define DMA_DIRECTION_INCREMENT                                  (DMASRCINCR_3)
#define DMA_INT_INACTIVE                                                  (0x0)
#define DMA_SIZE_SRCBYTE_DSTBYTE                      (DMASRCBYTE + DMADSTBYTE)
#define OFS_DMA0CTL            (0x0010)       /* DMA Channel 0 Control */
#define OFS_DMA0SA             (0x0012)       /* DMA Channel 0 Source Address */
#define DMA_TRANSFER_BLOCK                                            (DMADT_1)
#define DMA_TRIGGER_HIGH                                             (DMALEVEL)
#define DMA_TRIGGERSOURCE_0                                              (0x00)
#define OFS_DMA0DA             (0x0016)       /* DMA Channel 0 Destination Address */
#define OFS_DMA0SZ             (0x001A)       /* DMA Channel 0 Transfer Size */
#define DMA_TRANSFER_REPEATED_BURSTBLOCK                              (DMADT_6)
#define DMA_TRIGGERSOURCE_31                                             (0x1F)
#define bool   _Bool
#define false  0
#define true   1

void _DMA_setSrcAddress(uint8_t channelSelect,
                       uint32_t srcAddress,
                       uint16_t directionSelect);
void _DMA_setDstAddress(uint8_t channelSelect,
                       uint32_t dstAddress,
                       uint16_t directionSelect);
void _DMA_setTransferSize(uint8_t channelSelect,
                         uint16_t transferSize);
void _DMA_enableTransfers(uint8_t channelSelect);
void _DMA_disableTransfers(uint8_t channelSelect);
void _DMA_startTransfer(uint8_t channelSelect);
uint16_t _DMA_getInterruptStatus(uint8_t channelSelect);
bool _DMA_init(uint8_t channelSelect,
              uint16_t transferModeSelect,
              uint16_t transferSize,
              uint8_t triggerSourceSelect,
              uint8_t transferUnitSelect,
              uint8_t triggerTypeSelect);



#endif /* TRIK_DMA_H_ */
