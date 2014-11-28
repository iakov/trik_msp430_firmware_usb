/*
 * Trik_Motor.h
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */
#ifndef TRIK_MOTOR_H_
#define TRIK_MOTOR_H_

//Configuration parameters
#define DISABLE				0x00
#define ENABLE				0x01

//Motor mode
#define CONT_MODE           0x00
#define ANGLE_MODE          0x01
#define TIME_MODE           0x02

//Motor direction
#define FORWARD             0x00
#define BACKWARD            0x01

//Motor registers
#define MMCTL               0x00
#define MMDUT               0x01
#define MMPER               0x02
#define MMANG               0x03
#define MMTMR               0x04
#define MMVAL               0x05
#define MMSTA               0x06

//Motor errors
#define MOT_NO_ERROR        0x00

//Masks for bits of control register
#define MOT_ENABLE          0x8000 //Motor enable
#define MOT_AUTO            0x4000 //Autostop mode
#define MOT_ANGLE           0x2000 //Angle autostop mode
#define MOT_BACK            0x0010 //Backward direction
#define MOT_BRAKE           0x0008 //Brake enable
#define MOT_POWER           0x0003 //Motor power

//Max motors
#define MAX_MOTORS          0x04

//Prototypes for the APIs
void MOTOR_handler(uint8_t MOT_NUMBER);
void MOTOR_enableController(uint8_t MOT_NUMBER);
void MOTOR_disableController(uint8_t MOT_NUMBER);
//void MOTOR_rotationForward(uint8_t MOT_NUMBER);
//void MOTOR_rotationBackward(uint8_t MOT_NUMBER);
//void MOTOR_fastBrake(uint8_t MOT_NUMBER);
//void MOTOR_start(uint8_t MOT_NUMBER);
void MOTOR_stop(uint8_t MOT_NUMBER);

//Motor registers
struct tMotorRegisters
{
    uint16_t MCTL;
    uint16_t MDUT;
    uint16_t MPER;
    uint32_t MANG;
    uint32_t MTMR;
    uint32_t MVAL;
    uint16_t MSTA;
};

//Motors registers array
volatile struct tMotorRegisters MOT[MAX_MOTORS];

#endif
