/*
 * Trik_Devices.h
 *
 *  Created on: October 21, 2014
 *      Author: Rostislav Varzar
 */
#ifndef TRIK_DEVICES_H_
#define TRIK_DEVICES_H_

// Modules address table
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
#define SENSOR15            0x12
#define SENSOR16            0x13
#define SENSOR17            0x14
#define SENSOR18            0x15
#define ENCODER1			0x16
#define ENCODER2			0x17
#define ENCODER3			0x18
#define ENCODER4			0x19
#define PORT1   			0x1A
#define PORT2	    		0x1B
#define PORT3		    	0x1C
#define PORT4			    0x1D
#define PORT5			    0x1E
#define PORT6			    0x1F
#define PORTJ			    0x20
#define PWM1                0x21
#define PWM2                0x22
#define PWM3                0x23
#define PWM4                0x24
#define SENSCTRL            0x25
#define ASYNCTIMER          0x26
#define TOUCHDEVICE         0x27
#define I2C1                0x28
#define I2C2                0x29
#define I2C3                0x2A
#define I2C4                0x2B
#define I2C5                0x2C
#define I2C6                0x2D
#define I2C7                0x2E
#define BSL                 0xEE
#define NNONE				0xFF

// Modules versions
#define MAIN_VERSION        0x0025
#define MAIN_VERSION_TXT    "0.0.25"
#define MOTOR_VERSION       0x0025
#define SENSOR_VERSION      0x0025
#define ENCODER_VERSION     0x0025
#define PORT_VERSION        0x0025
#define PWM_VERSION         0x0025
#define ATIMER_VERSION      0x0025
#define TOUCH_VERSION       0x0025
#define I2C_VERSION         0x0025
#define BSL_VERSION         0x0025

// Slot free/busy defines
#define SLOT_FREE           0x00
#define SLOT_BUSY           0x01

// Max ports
#define MAX_DEVICES			I2C7

// Busy table
volatile uint8_t busy_table[MAX_DEVICES];

// Functions prototypes
void initGlobalVars();
void initReferenceTemperature();
void initADC10();
void initPBPorts();
uint8_t isSlotBusy(uint8_t DEV_NUMBER);
void reseveSlot(uint8_t DEV_NUMBER);
void releaseSlot(uint8_t DEV_NUMBER);
void resetTouch();

#endif
