/*
 * Trik_Devices.h
 *
 *  Created on: 21 окт. 2014 г.
 *      Author: Rostislav Varzar
 */
#ifndef TRIK_DEVICES_H_
#define TRIK_DEVICES_H_

#include <stdint.h>

//Devices
#define MOTOR1				0x00
#define MOTOR2				0x01
#define MOTOR3				0x02
#define MOTOR4				0x03
#define SENSOR1				0x04
#define SENSOR2				0x05
#define SENSOR3				0x06
#define SENSOR4				0x07
#define SENSOR5				0x08
#define SENSOR6				0x09
#define SENSOR7				0x0A
#define SENSOR8				0x0B
#define SENSOR9				0x0C
#define SENSOR10			0x0D
#define SENSOR11			0x0E
#define SENSOR12			0x0F
#define SENSOR13			0x10
#define SENSOR14			0x11
#define ENCODER1			0x12
#define ENCODER2			0x13
#define ENCODER3			0x14
#define ENCODER4			0x15
#define ACTUATOR1			0x16
#define ACTUATOR2			0x17
#define ACTUATOR3			0x18
#define ACTUATOR4			0x19
#define ACTUATOR5			0x1A
#define ACTUATOR6			0x1B
#define ACTUATOR7			0x1C
#define ACTUATOR8			0x1D
#define ACTUATOR9			0x1E
#define ACTUATOR10			0x1F
#define ACTUATOR11			0x20
#define ACTUATOR12			0x21
#define ACTUATOR13			0x22
#define ACTUATOR14			0x23
#define ACTUATOR15			0x24
#define ACTUATOR16			0x25
#define ACTUATOR17			0x26
#define ACTUATOR18			0x27
#define ACTUATOR19			0x28
#define ACTUATOR20			0x29
#define NNONE				0xFF

//Max ports
#define MAX_PORTS			0x30

//Trick ports
#define JM1					0x00
#define JM2					0x01
#define JM3					0x02
#define JM4					0x03
#define JA11				0x16
#define JA12				0x17
#define JA21				0x18
#define JA22				0x19
#define JA31				0x1A
#define JA32				0x1B
#define JA41				0x1C
#define JA42				0x1D
#define JA51				0x1E
#define JA52				0x1F
#define JA61				0x20
#define JA62				0x21
#define JB1A				0x0A
#define JB1B				0x0B
#define JB2A				0x0C
#define JB2B				0x0D
#define JB3A				0x0E
#define JB3B				0x0F
#define JB4A				0x10
#define JB4B				0x11

//Busy table
static uint8_t busy_table[MAX_PORTS]={100};

#endif
