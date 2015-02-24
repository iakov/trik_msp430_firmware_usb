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

//Defines for register numbers
#define TTMOD               0x00
#define TMINX               0x01
#define TMAXX               0x02
#define TMINY               0x03
#define TMAXY               0x04
#define TSCRX               0x05
#define TSCRY               0x06
#define TCURX               0x07
#define TCURY               0x08
#define TCVER               0x09

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
    uint16_t CURX;
    uint16_t CURY;
};

//Motors registers array
volatile struct tTouchRegisters TOUCH;

//Touch HID report
typedef struct {
    uint8_t buttons;
    uint8_t lx;
    uint8_t hx;
    uint8_t ly;
    uint8_t hy;
} MOUSE_REPORT;

volatile MOUSE_REPORT mouseReport;

#endif /* TRIK_TOUCH_H_ */
