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
#include "trik_async.h"

uint8_t DHT_read(uint8_t SENS_NUMBER, uint8_t* out_data)
{
	const uint8_t *end_data = out_data + 6;
	register uint8_t tmp1 = 1;
	register uint16_t cnt1 = 0;
	register uint16_t cnt2 = 0;
	register uint16_t cnt3 = 0;

	out_data[0] = out_data[1] = out_data[2] = out_data[3] = out_data[4] = out_data[5] = 0;
	switch (SENS_NUMBER)
	{
		case SENSOR1:
			P6SEL &= ~BIT5;
			P6OUT &= ~BIT5;
			P6DIR |= BIT5;
			P6REN &= ~BIT5;
			// Wait 18ms for startup
			__delay_cycles(WAIT_18_MS);
			P6REN |= BIT5;
			P6OUT |= BIT5;
			P6DIR &= ~BIT5;
			// Wait 20-40us + 80us for response
			cnt1 = 0;
			while (P6IN & BIT5)
			{
				__delay_cycles(WAIT_1_US); cnt1 ++;
				if (cnt1 > 100)
					return DHT_NO_RESPONSE;
			}
			// Read data
			do {
				cnt1 = cnt2 = 0;
				cnt3++;
				// Wait 80us until DHT pullups
				while (!(P6IN & BIT5))
				{
					__delay_cycles(WAIT_1_US);
					cnt1 ++;
					if (cnt1 > 100)
						return DHT_ERROR_80us;
				}
				// Wait transmission
				while (P6IN & BIT5)
				{
					__delay_cycles(WAIT_1_US);
					cnt2 ++;
					if (cnt2 > 100)
						return DHT_TRANS_ERROR;
				}

				if ((cnt1 + cnt2) > 110) // Logic "one", if signal > 110us
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

uint32_t DHT_getTemp(uint8_t SENS_NUMBER)
{
	uint8_t dht_data[6];
	uint8_t dht_result;
	disableTimer_B();
	dht_result = DHT_read(SENS_NUMBER, dht_data);
	enableTimer_B();
	if (dht_result)
	{
		return DHT_MAIN_ERROR;
	}
	else
	{
		return ((uint16_t)(dht_data[3] << 8) | dht_data[4]);
	}

}

uint32_t DHT_getHum(uint8_t SENS_NUMBER)
{
	uint8_t dht_data[6];
	uint8_t dht_result;
	disableTimer_B();
	dht_result = DHT_read(SENS_NUMBER, dht_data);
	enableTimer_B();
	if (dht_result)
	{
		return DHT_MAIN_ERROR;
	}
	else
	{
		return ((uint16_t)(dht_data[1] * 256) + dht_data[2]);
	}

}

