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
#define PWM1                0x04
#define PWM2                0x05
#define PWM3                0x06
#define PWM4                0x07
#define PWM5                0x08
#define SENSOR1				0x09
#define SENSOR2				0x0A
#define SENSOR3				0x0B
#define SENSOR4				0x0C
#define SENSOR5				0x0D
#define SENSOR6				0x0E
#define SENSOR7				0x0F
#define SENSOR8				0x10
#define SENSOR9				0x11
#define SENSOR10			0x12
#define SENSOR11			0x13
#define SENSOR12			0x14
#define SENSOR13			0x15
#define SENSOR14			0x16
#define SENSOR15            0x17
#define SENSOR16            0x18
#define SENSOR17            0x19
#define SENSOR18            0x1A
#define ENCODER1			0x1B
#define ENCODER2			0x1C
#define ENCODER3			0x1D
#define ENCODER4			0x1E
#define PORT1   			0x1F
#define PORT2	    		0x20
#define PORT3		    	0x21
#define PORT4			    0x22
#define PORT5			    0x23
#define PORT6			    0x24
#define PORTJ			    0x25
#define ASYNCTIMER          0x26
#define TOUCHDEVICE         0x27
#define BSL                 0xEE
#define NNONE				0xFF

//Slot free/busy defines
#define SLOT_FREE           0x00
#define SLOT_BUSY           0x01

//Max ports
#define MAX_DEVICES			TOUCHDEVICE

//Busy table
volatile uint8_t busy_table[MAX_DEVICES];

void initGlobalVars();
void initReferenceTemperature();
void initADC10();
void initPBPorts();
uint8_t isSlotBusy(uint8_t DEV_NUMBER);
void reseveSlot(uint8_t DEV_NUMBER);
void releaseSlot(uint8_t DEV_NUMBER);
void resetTouch();

#endif
