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
#define MOTOR1				0x0000
#define MOTOR2				0x0001
#define MOTOR3				0x0002
#define MOTOR4				0x0003
#define SENSOR1				0x0004
#define SENSOR2				0x0005
#define SENSOR3				0x0006
#define SENSOR4				0x0007
#define SENSOR5				0x0008
#define SENSOR6				0x0009
#define SENSOR7				0x000A
#define SENSOR8				0x000B
#define SENSOR9				0x000C
#define SENSOR10			0x000D
#define SENSOR11			0x000E
#define SENSOR12			0x000F
#define SENSOR13			0x0010
#define SENSOR14			0x0011
#define ENCODER1			0x0012
#define ENCODER2			0x0013
#define ENCODER3			0x0014
#define ENCODER4			0x0015
#define ACTUATOR1			0x0016
#define ACTUATOR2			0x0017
#define ACTUATOR3			0x0018
#define ACTUATOR4			0x0019
#define ACTUATOR5			0x001A
#define ACTUATOR6			0x001B
#define ACTUATOR7			0x001C
#define ACTUATOR8			0x001D
#define ACTUATOR9			0x001E
#define ACTUATOR10			0x001F
#define ACTUATOR11			0x0020
#define ACTUATOR12			0x0021
#define ACTUATOR13			0x0022
#define ACTUATOR14			0x0023
#define ACTUATOR15			0x0024
#define ACTUATOR16			0x0025
#define ACTUATOR17			0x0026
#define ACTUATOR18			0x0027
#define ACTUATOR19			0x0028
#define ACTUATOR20			0x0029
#define NNONE				0xFFFF

//Max ports
#define MAX_PORTS			0x0030

//Trick ports
#define JM1					0x0000
#define JM2					0x0001
#define JM3					0x0002
#define JM4					0x0003
#define JA11				0x0016
#define JA12				0x0017
#define JA21				0x0018
#define JA22				0x0019
#define JA31				0x001A
#define JA32				0x001B
#define JA41				0x001C
#define JA42				0x001D
#define JA51				0x001E
#define JA52				0x001F
#define JA61				0x0020
#define JA62				0x0021
#define JB1A				0x000A
#define JB1B				0x000B
#define JB2A				0x000C
#define JB2B				0x000D
#define JB3A				0x000E
#define JB3B				0x000F
#define JB4A				0x0010
#define JB4B				0x0011

//Busy table
static uint8_t busy_table[MAX_PORTS]={100};

#endif
