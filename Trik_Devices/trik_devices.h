/*
 * Trik_Devices.h
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */
#ifndef TRIK_DEVICES_H_
#define TRIK_DEVICES_H_

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
#define ASYNCTIMER          0x30
#define BSL                 0xEE
#define NNONE				0xFF

//Max ports
#define MAX_DEVICES			0x31

//Busy table
volatile uint8_t busy_table[MAX_DEVICES];

void initGlobalVars();
void initReferenceTemperature();
void initADC10();
void initPBPorts();


#endif
