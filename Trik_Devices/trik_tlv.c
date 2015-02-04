/*
 * trik_tlv.c
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#include <assert.h>
#include <stdint.h>
#include <msp430f5510.h>
#include "trik_tlv.h"
#include "trik_regaccess.h"

void _TLV_getInfo(uint8_t tag,
                 uint8_t instance,
                 uint8_t *length,
                 uint16_t **data_address
                 )
{
        // TLV Structure Start Address
        char *TLV_address = (char*)TLV_START;

        while ((TLV_address < (char*)TLV_END)
               && ((*TLV_address != tag) || instance)   // check for tag and instance
               && (*TLV_address != TLV_TAGEND)) {       // do range check first
                if (*TLV_address == tag)
                        // repeat till requested instance is reached
                        instance--;
                // add (Current TAG address + LENGTH) + 2
                TLV_address += *(TLV_address + 1) + 2;
        }

        // Check if Tag match happened..
        if (*TLV_address == tag) {
                // Return length = Address + 1
                *length = *(TLV_address + 1);
                // Return address of first data/value info = Address + 2
                *data_address = (uint16_t*)(TLV_address + 2);
        }
        // If there was no tag match and the end of TLV structure was reached..
        else{
                // Return 0 for TAG not found
                *length = 0;
                // Return 0 for TAG not found
                *data_address = 0;
        }
}
