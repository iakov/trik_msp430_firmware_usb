/*
 * trik_dhtxx.c
 *
 *  Created on: July 21, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <msp430f5510.h>
#include "trik_dhtxx.h"
#include "trik_sensor.h"
#include "trik_devices.h"

uint16_t DHT_read(uint8_t SENS_NUMBER, uint8_t* out_data)
{

	const uint8_t *end_data = out_data + 6;
	register uint16_t stmp, etmp;
	register uint8_t tmp1 = 1;

	out_data[0] = out_data[1] = out_data[2] = out_data[3] = out_data[4] = out_data[5] = 0;
	switch (SENS_NUMBER)
	{
		case SENSOR1:
			P6SEL &= ~BIT5;
			P6OUT &= ~BIT5;
			P6DIR |= BIT5;
			P6REN &= ~BIT5;
			stmp = TB0R;
			while((TB0R - stmp) < 54000)
				;  // Wait 18ms
			P6REN |= BIT5;
			P6OUT |= BIT5;
			P6DIR &= ~BIT5;
			// Wait 20-40us + 80us for response
			stmp = TB0R;
			while (P6IN & BIT5)
			{
				if ((TB0R - stmp) > 300)
					return DHT_NO_RESPONSE;
			}
			// Read data
			etmp = TB0R;
			do {
				// Wait 80us until DHT pullups
				stmp = etmp;
				while (!(P6IN & BIT5))
				{
					if ((TB0R - stmp) > 300)
						return DHT_ERROR_80us;
				}
				// Wait transmission
				while (P6IN & BIT5)
				{
					if ((TB0R - stmp) > 600)
						return DHT_TRANS_ERROR;
				}
				// Get end time
				etmp = TB0R;
				if ((etmp - stmp) > 330) // Logic "one", if signal > 110us
					*out_data |= tmp1;
				if (!(tmp1 >>= 1))
				{
					tmp1 = 0x80;
					++out_data;
				}
			} while (out_data < end_data);
			out_data -= 6;
			if (out_data[0] != 1)
				return DHT_NO_START;
			if (((out_data[1] + out_data[2] + out_data[3] + out_data[4]) & 0xFF) != out_data[5])
				return DHT_BAD_CRC;
			break;
		default:
			return DHT_SENS_NUM;
	}
	return DHT_NO_ERROR;
}

uint16_t DHT_getTemp(uint8_t SENS_NUMBER)
{
	uint8_t dht_data[6];
	return DHT_read(SENS_NUMBER, dht_data);
}

uint16_t DHT_getHum(uint8_t SENS_NUMBER)
{
	uint8_t dht_data[6];
	return DHT_read(SENS_NUMBER, dht_data);
}

