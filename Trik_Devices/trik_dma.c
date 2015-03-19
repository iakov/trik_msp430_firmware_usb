/*
 * trik_dma.c
 *
 *  Imported from driverlib: Fabruary 4, 2015
 */

//#include <assert.h>
#include <stdint.h>
#include <msp430f5510.h>
#include "trik_dma.h"
#include "trik_regaccess.h"

void _DMA_setSrcAddress(uint8_t channelSelect,
                       uint32_t srcAddress,
                       uint16_t directionSelect)
{
        //assert(channelSelect <= DMA_CHANNEL_7);
        //assert(directionSelect <= DMA_DIRECTION_INCREMENT);

        //Set the Source Address
        __data16_write_addr((unsigned short)(DMA_BASE + channelSelect + OFS_DMA0SA),
                            srcAddress);

        //Reset bits before setting them
        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) &= ~(DMASRCINCR_3);
        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) |= directionSelect;
}

void _DMA_setDstAddress(uint8_t channelSelect,
                       uint32_t dstAddress,
                       uint16_t directionSelect)
{
        //assert(channelSelect <= DMA_CHANNEL_7);
        //assert(directionSelect <= DMA_DIRECTION_INCREMENT);

        //Set the Destination Address
        __data16_write_addr((unsigned short)(DMA_BASE + channelSelect + OFS_DMA0DA),
                            dstAddress);

        //Reset bits before setting them
        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) &= ~(DMADSTINCR_3);
        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) |= (directionSelect << 2);
}

void _DMA_setTransferSize(uint8_t channelSelect,
                         uint16_t transferSize)
{
        //Set Transfer Size Amount
        HWREG16(DMA_BASE + channelSelect + OFS_DMA0SZ) = transferSize;
}

void _DMA_enableTransfers(uint8_t channelSelect)
{
        //assert(channelSelect <= DMA_CHANNEL_7);

        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) |= DMAEN;
}

void _DMA_disableTransfers(uint8_t channelSelect)
{
        //assert(channelSelect <= DMA_CHANNEL_7);

        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) &= ~(DMAEN);
}

void _DMA_startTransfer(uint8_t channelSelect)
{
        //assert(channelSelect <= DMA_CHANNEL_7);

        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) |= DMAREQ;
}

uint16_t _DMA_getInterruptStatus(uint8_t channelSelect)
{
        //assert(channelSelect <= DMA_CHANNEL_7);

        return HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) & DMAIFG;
}

bool _DMA_init(uint8_t channelSelect,
              uint16_t transferModeSelect,
              uint16_t transferSize,
              uint8_t triggerSourceSelect,
              uint8_t transferUnitSelect,
              uint8_t triggerTypeSelect)
{
        //assert(channelSelect <= DMA_CHANNEL_7);
        //assert(transferModeSelect <= DMA_TRANSFER_REPEATED_BURSTBLOCK);
        //assert(triggerSourceSelect <= DMA_TRIGGERSOURCE_31);
        //assert(transferUnitSelect <= DMA_SIZE_SRCBYTE_DSTBYTE);
        //assert(triggerTypeSelect <= DMA_TRIGGER_HIGH);

        bool retVal = STATUS_SUCCESS;
        uint8_t triggerOffset = (channelSelect >> 4);

        //Reset and Set DMA Control 0 Register
        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) =
                transferModeSelect      //Set Transfer Mode
                + transferUnitSelect    //Set Transfer Unit Size
                + triggerTypeSelect;    //Set Trigger Type

        //Set Transfer Size Amount
        HWREG16(DMA_BASE + channelSelect + OFS_DMA0SZ) = transferSize;

        if (triggerOffset & 0x01) {                                     //Odd Channel
                HWREG16(DMA_BASE + (triggerOffset & 0x0E)) &= 0x00FF;   //Reset Trigger Select
                HWREG16(DMA_BASE +
                        (triggerOffset & 0x0E)) |= (triggerSourceSelect << 8);
        } else {                                                        //Even Channel
                HWREG16(DMA_BASE + (triggerOffset & 0x0E)) &= 0xFF00;   //Reset Trigger Select
                HWREG16(DMA_BASE + (triggerOffset & 0x0E)) |= triggerSourceSelect;
        }

        return retVal;
}
