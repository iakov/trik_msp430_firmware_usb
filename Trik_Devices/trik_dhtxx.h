/*
 * trik_dhtxx.h
 *
 *  Created on: July 21, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_DEVICES_TRIK_DHTXX_H_
#define TRIK_DEVICES_TRIK_DHTXX_H_

void DHT_read(uint8_t SENS_NUMBER);
uint16_t DHT_getTemp(uint8_t SENS_NUMBER);
uint16_t DHT_getHum(uint8_t SENS_NUMBER);

#endif /* TRIK_DEVICES_TRIK_DHTXX_H_ */
