/*
 * trik_port.c
 *
 *  Created on: November 28, 2014
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include "trik_port.h"
#include "driverlib.h"

//Write to port
void PORT_write(uint8_t PORT_NUMBER, uint8_t REG_ADDRESS, uint8_t REG_VALUE)
{

}

//Read from port
uint8_t PORT_read(uint8_t PORT_NUMBER, uint8_t REG_ADDRESS)
{
    return 0x00;
}
