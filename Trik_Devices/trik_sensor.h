/*
 * trik_sensor.h
 *
 *  Created on: October 31, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SENSOR_H_
#define TRIK_SENSOR_H_

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
    uint16_t MCTL;
    uint16_t MPWR;
    uint16_t MFRQ;
    uint16_t MANG;
    uint16_t MTMR;
    uint32_t MVAL;
    uint16_t MSTA;
    uint8_t MOT_EN;
    uint8_t MOT_PWR;
    uint8_t MOT_DIR;
    uint8_t MOT_BRK;
};

//Motors registers array
struct tSensorRegisters SENS[MAX_SENSORS];



#endif /* TRIK_SENSOR_H_ */
