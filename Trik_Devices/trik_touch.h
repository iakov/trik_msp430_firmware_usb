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

uint8_t isTouched();
uint16_t touchReadX();
uint16_t touchReadY();


#endif /* TRIK_TOUCH_H_ */
