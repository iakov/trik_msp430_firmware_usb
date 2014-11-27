/*
 * trik_async.h
 *
 *  Created on: November 11, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_ASYNC_H_
#define TRIK_ASYNC_H_

//Timer registers defines
#define AATCTL 0x00
#define AATPER 0x01
#define AATVAL 0x02

//Timer period defines
#define NORMAL_PERIOD 0x0960
#define MAXIMUM_PERIOD 0xFFFF

void enableTimer_B();
void disableTimer_B();
uint8_t ASYNCTIMER_hadler();

//Timer registers
struct tTimerRegisters
{
    uint16_t ATCTL;
    uint16_t ATPER;
    uint32_t ATVAL;
};

//Timer register struct
volatile struct tTimerRegisters ASYNCTMR;

#endif /* TRIK_ASYNC_H_ */
