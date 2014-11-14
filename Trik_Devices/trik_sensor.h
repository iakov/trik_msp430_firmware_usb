/*
 * trik_sensor.h
 *
 *  Created on: October 31, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_SENSOR_H_
#define TRIK_SENSOR_H_

//Configuration parameters
#define DISABLE 0
#define ENABLE  1

//Sensor registers
#define SSCTL 0x00
#define SSIDX 0x01
#define SSVAL 0x02
#define SSSTA 0x03

//Sensor mode
#define SING_MODE 0
#define CONT_MODE 1

//Sensor types
#define DIGITAL_INP     0x0000
#define ANALOG_INP      0x0001
#define MOTOR_VOLTAGE   0x0002
#define MOTOR_CURRENT   0x0003
#define MCU_TEMP        0x0004
#define DIST_SENSOR     0x0004

//Prototypes for the APIs
uint8_t SENSOR_hadler(uint8_t SENS_NUMBER);
uint32_t SENSOR_read_digital(uint8_t SENS_NUMBER);
uint32_t SENSOR_read_analog(uint8_t SENS_NUMBER);
uint32_t SENSOR_read_voltage(uint8_t SENS_NUMBER);
uint32_t SENSOR_read_current(uint8_t SENS_NUMBER);
uint32_t SENSOR_read_temperature(uint8_t SENS_NUMBER);
uint32_t SENSOR_read_distance(uint8_t SENS_NUMBER);
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
    uint8_t SENS_MOD;
    uint8_t SENS_PUP;
};

//Motors registers array
struct tSensorRegisters SENS[MAX_SENSORS];



#endif /* TRIK_SENSOR_H_ */
