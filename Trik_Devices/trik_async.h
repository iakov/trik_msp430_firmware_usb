/*
 * trik_async.h
 *
 *  Created on: November 11, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_ASYNC_H_
#define TRIK_ASYNC_H_

// Timer registers defines
#define AATCTL               0x00
#define AATPER               0x01
#define AATVAL               0x02
#define AATVER               0x03

// Timer period defines
//#define NORMAL_PERIOD        0x0960    //Overflow interrupt frequency is 10 kHz (div 1)
#define NORMAL_PERIOD        0x012C    //Overflow interrupt frequency is 10 kHz (div 8)
//#define NORMAL_PERIOD        0x04B0
#define MAXIMUM_PERIOD       0xFFFF

// Timer enable mask bit
#define AT_EN                0x0003

void enableTimer_B();
void disableTimer_B();

// Timer registers
struct tTimerRegisters
{
    uint16_t ATCTL;
    uint16_t ATPER;
    uint32_t ATVAL;
};

// Timer registers struct
volatile struct tTimerRegisters ASYNCTMR;

#endif /* TRIK_ASYNC_H_ */
