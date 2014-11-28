/*
 * trik_port.h
 *
 *  Created on: November 28, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_PORT_H_
#define TRIK_PORT_H_

//Registers
#define PIN             0x00
#define POUT            0x01
#define PDIR            0x02
#define PREN            0x03
#define PDS             0x04
#define PSEL            0x05
#define PIE             0x06
#define PIES            0x07
#define PIFG            0x08

//Prototypes for the APIs
void PORT_write(uint8_t PORT_NUMBER, uint8_t REG_ADDRESS, uint8_t REG_VALUE);
uint8_t PORT_read(uint8_t PORT_NUMBER, uint8_t REG_ADDRESS);


#endif /* TRIK_PORT_H_ */
