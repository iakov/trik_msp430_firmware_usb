/*
 * trik_tlv.h
 *
 *  Created on: Fabruary 4, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_TLV_H_
#define TRIK_TLV_H_

#define TLV_TAG_DIERECORD                                         TLV_DIERECORD

void _TLV_getInfo(uint8_t tag,
                 uint8_t instance,
                 uint8_t *length,
                 uint16_t **data_address
                 );


#endif /* TRIK_TLV_H_ */
