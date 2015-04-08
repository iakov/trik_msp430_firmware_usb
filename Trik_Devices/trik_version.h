/*
 * trik_version.h
 *
 *  Created on: February 24, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_VERSION_H_
#define TRIK_VERSION_H_

// Modules versions
#define MAIN_VERSION_TXT    "0.0.30\n\0"
#define MAIN_VERSION        30
#define MOTOR_VERSION       2
#define SENSOR_VERSION      1
#define ENCODER_VERSION     1
#define PORT_VERSION        1
#define PWM_VERSION         2
#define SPWM_VERSION        1
#define ATIMER_VERSION      1
#define TOUCH_VERSION       1
#define I2C_VERSION         4
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

#endif /* TRIK_VERSION_H_ */
