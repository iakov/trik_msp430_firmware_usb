/* --COPYRIGHT--,BSD
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

//
//! \cond
//

/* 
 * ======== dma.c ========
 */
#include <string.h>
#include "../USB_Common/device.h"
#include "../USB_Common/defMSP430USB.h"
#include <descriptors.h>
#include <string.h>
#include <assert.h>

#ifdef __REGISTER_MODEL__
/* for IAR */
#   if __REGISTER_MODEL__ == __REGISTER_MODEL_REG20__
#       define __DMA_ACCESS_REG__ (void __data20 *)
#   else
#       define __DMA_ACCESS_REG__ (uint16_t)
#   endif
#else
/* for CCS */
#   define __DMA_ACCESS_REG__ (__SFR_FARPTR)(uint32_t)
#endif

//Copied from driverlib dma.c
#define DMA_CHANNEL_7                                                    (0x70)
#define DMA_DIRECTION_INCREMENT                                  (DMASRCINCR_3)
#define DMA_INT_INACTIVE                                                  (0x0)
#define DMA_SIZE_SRCBYTE_DSTBYTE                      (DMASRCBYTE + DMADSTBYTE)
#define OFS_DMA0CTL            (0x0010)       /* DMA Channel 0 Control */
#define OFS_DMA0SA             (0x0012)       /* DMA Channel 0 Source Address */
#define HWREG16(x)                                                             \
        (*((volatile uint16_t*)((uint16_t)x)))
#define DMA_TRANSFER_BLOCK                                            (DMADT_1)
#define DMA_TRIGGER_HIGH                                             (DMALEVEL)
#define DMA_TRIGGERSOURCE_0                                              (0x00)
#define OFS_DMA0DA             (0x0016)       /* DMA Channel 0 Destination Address */
#define OFS_DMA0SZ             (0x001A)       /* DMA Channel 0 Transfer Size */
#define bool   _Bool
#define false  0
#define true   1
#define DMA_TRANSFER_REPEATED_BURSTBLOCK                              (DMADT_6)
#define DMA_TRIGGERSOURCE_31                                             (0x1F)
#define STATUS_SUCCESS  0x01

void _DMA_setSrcAddress(uint8_t channelSelect,
                       uint32_t srcAddress,
                       uint16_t directionSelect)
{
        assert(channelSelect <= DMA_CHANNEL_7);
        assert(directionSelect <= DMA_DIRECTION_INCREMENT);

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
        assert(channelSelect <= DMA_CHANNEL_7);
        assert(directionSelect <= DMA_DIRECTION_INCREMENT);

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
        assert(channelSelect <= DMA_CHANNEL_7);

        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) |= DMAEN;
}

void _DMA_disableTransfers(uint8_t channelSelect)
{
        assert(channelSelect <= DMA_CHANNEL_7);

        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) &= ~(DMAEN);
}

void _DMA_startTransfer(uint8_t channelSelect)
{
        assert(channelSelect <= DMA_CHANNEL_7);

        HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) |= DMAREQ;
}

uint16_t _DMA_getInterruptStatus(uint8_t channelSelect)
{
        assert(channelSelect <= DMA_CHANNEL_7);

        return HWREG16(DMA_BASE + channelSelect + OFS_DMA0CTL) & DMAIFG;
}

bool _DMA_init(uint8_t channelSelect,
              uint16_t transferModeSelect,
              uint16_t transferSize,
              uint8_t triggerSourceSelect,
              uint8_t transferUnitSelect,
              uint8_t triggerTypeSelect)
{
        assert(channelSelect <= DMA_CHANNEL_7);
        assert(transferModeSelect <= DMA_TRANSFER_REPEATED_BURSTBLOCK);
        assert(triggerSourceSelect <= DMA_TRIGGERSOURCE_31);
        assert(transferUnitSelect <= DMA_SIZE_SRCBYTE_DSTBYTE);
        assert(triggerTypeSelect <= DMA_TRIGGER_HIGH);

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

//function pointers
void *(*USB_TX_memcpy)(void * dest, const void * source, size_t count);
void *(*USB_RX_memcpy)(void * dest, const void * source, size_t count);

void * memcpyDMA0 (void * dest, const void * source, size_t count);
void * memcpyDMA1 (void * dest, const void * source, size_t count);
void * memcpyDMA2 (void * dest, const void * source, size_t count);

//NOTE: this functin works only with data in the area <64k (small memory model)
void * memcpyV (void * dest, const void * source, size_t count)
{
    uint16_t i;
    volatile uint8_t bTmp;

    for (i = 0; i < count; i++)
    {
        bTmp = *((uint8_t*)source + i);
        *((uint8_t*)dest  + i) = bTmp;
    }
    return (dest);
}

void * memcpyDMA (void * dest, const void *  source, size_t count)
{
    if (count == 0){                                        //do nothing if zero bytes to transfer
        return (dest);
    }

    //DMA4 workaround - disable DMA transfers during read-modify-write CPU 
    //operations
#ifndef DRIVERLIB_LEGACY_MODE
    DMACTL4 |= DMARMWDIS; //DMA_disableTransferDuringReadModifyWrite();
    _DMA_setSrcAddress(USB_DMA_CHAN, (uint32_t)source, DMA_DIRECTION_INCREMENT);
    _DMA_setDstAddress(USB_DMA_CHAN, (uint32_t)dest, DMA_DIRECTION_INCREMENT);
    //DMA4 workaround - re-enable DMA transfers during read-modify-write CPU 
    //operations
    DMACTL4 &= ~(DMARMWDIS); //DMA_enableTransferDuringReadModifyWrite();
    _DMA_setTransferSize(USB_DMA_CHAN, count);
    _DMA_enableTransfers(USB_DMA_CHAN);
    _DMA_startTransfer(USB_DMA_CHAN);

    while (_DMA_getInterruptStatus(USB_DMA_CHAN) == DMA_INT_INACTIVE);

    _DMA_disableTransfers(USB_DMA_CHAN);
#else

    //DMACTL4 |= DMARMWDIS; //DMA_disableTransferDuringReadModifyWrite(DMA_BASE);
    //DMA_setSrcAddress(DMA_BASE, USB_DMA_CHAN, (uint32_t)source, DMA_DIRECTION_INCREMENT);
    //DMA_setDstAddress(DMA_BASE, USB_DMA_CHAN, (uint32_t)dest, DMA_DIRECTION_INCREMENT);
    //DMA4 workaround - re-enable DMA transfers during read-modify-write CPU 
    //operations
    //DMACTL4 &= ~(DMARMWDIS); //DMA_enableTransferDuringReadModifyWrite(DMA_BASE);
    //DMA_setTransferSize(DMA_BASE, USB_DMA_CHAN, count);
    //DMA_enableTransfers(DMA_BASE, USB_DMA_CHAN);
    //DMA_startTransfer(DMA_BASE, USB_DMA_CHAN);

    //while (DMA_getInterruptStatus(DMA_BASE, USB_DMA_CHAN) == DMA_INT_INACTIVE);

    //DMA_disableTransfers(DMA_BASE, USB_DMA_CHAN);
#endif

    return (dest);
}

//this function inits the DMA
void USB_initMemcpy (void)
{
    USB_TX_memcpy = memcpyV;
    USB_RX_memcpy = memcpyV;

    if (USB_DMA_CHAN != 0xFF) {
#ifndef DRIVERLIB_LEGACY_MODE
    	_DMA_init (USB_DMA_CHAN, DMA_TRANSFER_BLOCK, 0,
    		DMA_TRIGGERSOURCE_0, DMA_SIZE_SRCBYTE_DSTBYTE, DMA_TRIGGER_HIGH);
#else
       // DMA_init (DMA_BASE, USB_DMA_CHAN, DMA_TRANSFER_BLOCK, 0,
    	//	DMA_TRIGGERSOURCE_0, DMA_SIZE_SRCBYTE_DSTBYTE, DMA_TRIGGER_HIGH);
#endif
        USB_TX_memcpy = memcpyDMA;
        USB_RX_memcpy = memcpyDMA;
    }
}

//
//! \endcond
//

/*----------------------------------------------------------------------------+
 | End of source file                                                          |
 +----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
//Released_Version_4_10_02
