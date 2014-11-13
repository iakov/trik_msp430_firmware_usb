/*
 * trik_sensor.h
 *
 *  Created on: October 31, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SENSOR_H_
#define TRIK_SENSOR_H_

//Sensor registers
#define SSCTL 0x00
#define SSIDX 0x01
#define SSVAL 0x02
#define SSSTA 0x03


//Prototypes for the APIs
uint8_t SENSOR_hadler(uint8_t SENS_NUMBER);
uint32_t SENSOR_read(uint8_t SENS_NUMBER);
void SENSOR_enableController(uint8_t MOT_NUMBER);
void SENSOR_disableController(uint8_t MOT_NUMBER);

//Max motors
#define MAX_SENSORS 14

//Motor registers
struct tSensorRegisters
{
    uint16_t SCTL;
    uint16_t SIDX;
    uint32_t SVAL;
    uint16_t SSTA;
    uint8_t SENS_EN;
};

//Motors registers array
struct tSensorRegisters SENS[MAX_SENSORS];



#endif /* TRIK_SENSOR_H_ */
