/*
 * trik_version.h
 *
 *  Created on: February 24, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_VERSION_H_
#define TRIK_VERSION_H_

// Modules versions
#define MAIN_VERSION_TXT    "0.0.35\n\0"
#define MAIN_VERSION        35
#define MOTOR_VERSION       3
#define SENSOR_VERSION      2
#define ENCODER_VERSION     2
#define PORT_VERSION        1
#define HPWM_VERSION		3
#define SPWM_VERSION        1
#define ATIMER_VERSION      3
#define TOUCH_VERSION       1
#define I2C_VERSION         4
#define USART_VERSION       1
#define BSL_VERSION         1

// Version registers adresses defines
#define MAIN_VER_REG_1      0x00
#define MAIN_VER_REG_2      0x01
#define MOT_VER_REG         0x02
#define SENS_VER_REG        0x03
#define ENC_VER_REG         0x04
#define PORT_VER_REG        0x05
#define PWM_VER_REG         0x06
#define ATMR_VER_REG        0x07
#define TOUCH_VER_REG       0x08
#define I2C_VER_REG         0x09
#define BSL_VER_REG         0x0A
#define SPWM_VER_REG        0x0B
#define USART_VER_REG		0x0C

#endif /* TRIK_VERSION_H_ */
