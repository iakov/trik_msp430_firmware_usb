/*
 * trik_touch.c
 *
 *  Created on: December 1, 2014
 *      Author: Rostislav Varzar
 */

//Return 1, if panel is touched
uint8_t isTouched()
{
    P2DIR &= ~(BIT0+BIT3);
}
