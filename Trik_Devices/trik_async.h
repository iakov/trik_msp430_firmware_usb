/*
 * trik_async.h
 *
 *  Created on: November 11, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_ASYNC_H_
#define TRIK_ASYNC_H_

#define MAX_STRING_LENGTH 32

//Timer registers
struct tTimerRegisters
{
    uint16_t ATCTL;
    uint32_t ATVAL;
};

//Timer register struct
struct tTimerRegisters ASYNCTMR;

void enableTimer_B();
void disableTimer_B();
uint8_t ASYNCTIMER_hadler();


#endif /* TRIK_ASYNC_H_ */
