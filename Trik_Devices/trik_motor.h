/*
 * Trik_Motor.h
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */
#ifndef TRIK_MOTOR_H_
#define TRIK_MOTOR_H_

#include <stdint.h>
#include "trik_devices.h"

//Configuration parameters
#define DISABLE				0
#define ENABLE				1
#define CONT_MODE			0
#define SINGLE_MODE			1
#define	TIME_MODE			0
#define	ANGLE_MODE			0
#define SENS_1WIRE			0
#define SENS_2WIRE			1
#define SENS_ANALOG			2
#define SENS_CNT00			0
#define SENS_CNT01			1
#define SENS_CNT10			2
#define SENS_CNT11			3
#define SENS_CNT20			4
#define SENS_CNT21			5
#define SENS_CNT30			6
#define SENS_CNT31			7
#define DIR_FOR				0
#define DIR_BACK			1
#define	BRAKE_OFF			0
#define	BRAKE_ON			1


//Prototypes for the APIs
uint8_t MOTOR_hadler(uint8_t MOT_NUMBER);
void MOTOR_enableController(uint8_t MOT_NUMBER);
void MOTOR_disableController(uint8_t MOT_NUMBER);
//void MOTOR_setContinuesMode(uint8_t MOT_NUMBER);
//void MOTOR_setSingleTimeMode(uint8_t MOT_NUMBER);
//void MOTOR_setSingleAngleMode(uint8_t MOT_NUMBER);
//void MOTOR_enableFeedBackSensor(uint8_t MOT_NUMBER);
//void MOTOR_disableFeedBackSensor(uint8_t MOT_NUMBER);
//void MOTOR_set1wireSensor(uint8_t MOT_NUMBER);
//void MOTOR_set2wireSensor(uint8_t MOT_NUMBER);
//void MOTOR_setAnalogSensor(uint8_t MOT_NUMBER);
//void MOTOR_setSensorPort(uint8_t MOT_NUMBER, uint8_t SENSPORT_NUMBER);
//void MOTOR_resetFeedBackSensor(uint8_t MOT_NUMBER);
void MOTOR_rotationForward(uint8_t MOT_NUMBER);
void MOTOR_rotationBackward(uint8_t MOT_NUMBER);
void MOTOR_enableBrake(uint8_t MOT_NUMBER);
void MOTOR_disableBrake(uint8_t MOT_NUMBER);
void MOTOR_fastBrake(uint8_t MOT_NUMBER);
//void MOTOR_setPower(uint8_t MOT_NUMBER, uint16_t MOT_POWER);
//void MOTOR_setFrequency(uint8_t MOT_NUMBER, uint16_t MOT_FREQ);
//void MOTOR_setAngle(uint8_t MOT_NUMBER, uint16_t MOT_ANGLE);
//void MOTOR_setTimer(uint8_t MOT_NUMBER, uint16_t MOT_TIME);
//uint32_t MOTOR_getSensorValue(uint8_t MOT_NUMBER);
//uint8_t MOTOR_isError(uint8_t MOT_NUMBER);
//uint8_t MOTOR_isOverPower(uint8_t MOT_NUMBER);
//uint8_t MOTOR_isWorking(uint8_t MOT_NUMBER);
void MOTOR_start(uint8_t MOT_NUMBER);
void MOTOR_stop(uint8_t MOT_NUMBER);

//Motor registers
struct tMotorRegisters
{
    uint16_t MCTL;
    uint16_t MPWR;
    uint16_t MFRQ;
    uint16_t MANG;
    uint16_t MTMR;
    uint32_t MVAL;
    uint16_t MSTA;
    bool MOT_EN;
    bool MOT_PWR;
    bool MOT_DIR;
    bool MOT_PWM;
    bool MOT_BRK;
};

//Motors registers array
struct tMotorRegisters MOT[MAX_MOTORS];


#endif
