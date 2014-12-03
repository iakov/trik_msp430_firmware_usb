/*
 * trik_touch.h
 *
 *  Created on: December 1, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_TOUCH_H_
#define TRIK_TOUCH_H_

#define NOT_TOUCHED         0x00
#define TOUCHED             0xFF

#define CAL_OFF             0x00
#define CAL_ON              0x01


uint8_t isTouched();
uint16_t touchReadX();
uint16_t touchReadY();
void startCal();
void stopCal();

//Touch registers
struct tTouchRegisters
{
    uint16_t TMOD;
    uint16_t MINX;
    uint16_t MAXX;
    uint16_t MINY;
    uint16_t MAXY;
    uint16_t SCRX;
    uint16_t SCRY;
};

//Motors registers array
volatile struct tTouchRegisters TOUCH;



volatile uint8_t cal_mode;

#endif /* TRIK_TOUCH_H_ */
