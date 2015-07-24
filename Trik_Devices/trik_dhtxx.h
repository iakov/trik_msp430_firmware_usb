/*
 * trik_dhtxx.h
 *
 *  Created on: July 21, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_DEVICES_TRIK_DHTXX_H_
#define TRIK_DEVICES_TRIK_DHTXX_H_

#define DHT_NO_ERROR		0x00
#define DHT_READ_ERR		0xFF

uint16_t DHT_read(uint8_t SENS_NUMBER, char* out_data);
uint16_t DHT_getTemp(uint8_t SENS_NUMBER);
uint16_t DHT_getHum(uint8_t SENS_NUMBER);

#endif /* TRIK_DEVICES_TRIK_DHTXX_H_ */
