/*
 * trik_dhtxx.h
 *
 *  Created on: July 21, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_DEVICES_TRIK_DHTXX_H_
#define TRIK_DEVICES_TRIK_DHTXX_H_

#define DHT_NO_ERROR		0x00
#define DHT_NO_RESPONSE		0x01
#define DHT_ERROR_80us		0x02
#define DHT_TRANS_ERROR		0x03
#define DHT_NO_START		0x04
#define DHT_BAD_CRC			0x05
#define DHT_SENS_NUM		0xFF

uint16_t DHT_read(uint8_t SENS_NUMBER, uint8_t* out_data);
uint16_t DHT_getTemp(uint8_t SENS_NUMBER);
uint16_t DHT_getHum(uint8_t SENS_NUMBER);

#endif /* TRIK_DEVICES_TRIK_DHTXX_H_ */
