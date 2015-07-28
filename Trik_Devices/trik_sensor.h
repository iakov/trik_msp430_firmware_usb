/*
 * trik_sensor.h
 *
 *  Created on: October 31, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SENSOR_H_
#define TRIK_SENSOR_H_

// Sensor registers
#define SSCTL			0x00
#define SSIDX			0x01
#define SSVAL			0x02
#define SSVER			0x03

// Sensor types
#define DIGITAL_INP		0x0000
#define ANALOG_INP		0x0001
#define DHTXX_TEMP		0x0002
#define DHTXX_HUM		0x0003

// Sensor errors
#define SENS_NO_ERROR	0x00

// Max sensors
#define MAX_SENSORS	18

// Masks for bits of control register
#define SENS_ENABLE		0x8000	// Enable bit
#define SENS_ASYNC		0x4000	// Async mode
#define SENS_PULL		0x2000	// Pull up resistors
#define SENS_READ		0x0001	// Sensor read

// Functions prototypes
uint32_t SENSOR_read_digital(uint8_t SENS_NUMBER);
uint32_t SENSOR_read_analog(uint8_t SENS_NUMBER);
void SENSOR_enableController(uint8_t SENS_NUMBER);
void SENSOR_disableController(uint8_t SENS_NUMBER);

// Sensor registers
struct tSensorRegisters
{
	uint16_t SCTL;
	uint16_t SIDX;
	uint32_t SVAL;
	uint16_t SSTA;
};

// Sensor registers array
volatile struct tSensorRegisters SENS[MAX_SENSORS];

#endif /* TRIK_SENSOR_H_ */
