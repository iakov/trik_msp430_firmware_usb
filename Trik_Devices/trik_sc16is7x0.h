/*
 * trik_sc16is7x0.h
 *
 *  Created on: May 26, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_DEVICES_TRIK_SC16IS7X0_H_
#define TRIK_DEVICES_TRIK_SC16IS7X0_H_

// USART errors
#define USART_NO_ERROR		0x00
#define USART_DEV_ERROR		0xFF

// Masks for bits of control register
#define USART_EN			0x80000000 // USART enable
#define USART_EVEN			0x40000000 // USART even parity
#define USART_ODD			0x20000000 // USART odd parity
#define USART_2SB			0x10000000 // USART 1.5 or 2 stop bits
#define USART_6BITS			0x04000000 // USART 6 bits word length
#define USART_7BITS			0x08000000 // USART 7 bits word length
#define USART_8BITS			0x0C000000 // USART 8 bits word length
#define USART_IRDA1			0x00800000 // USART IrDA 115.2 kbaud mode
#define USART_IRDA2			0x01000000 // USART IrDA 1.152 Mbaud mode
#define USART_RS485			0x01800000 // USART RS-485 mode
#define USART_RS485M		0x02000000 // USART RS-485 9 bits mode
#define USART_INVRTS		0x00400000 // USART RTS inverted mode
#define USART_RXEN			0x00200000 // USART receiver enable
#define USART_TXEN			0x00100000 // USART transmitter enable
#define USART_RTS			0x00080000 // USART RTS high level
#define USART_DTR			0x00040000 // USART DTR high level
#define USART_RST			0x00000003 // USART software reset

// Maximum of USARTs
#define MAX_USARTS			0x07

// Registers
#define UUCTL				0x00
#define UUSPD				0x01
#define UUSTA				0x02
#define UUDAT				0x03

// USART registers
struct tUSARTRegisters
{
	uint32_t UCTL;
	uint32_t USPD;
	uint32_t USTA;
	uint8_t UDAT;
};

// USART registers array
volatile struct tUSARTRegisters USART[MAX_USARTS];


#endif /* TRIK_DEVICES_TRIK_SC16IS7X0_H_ */
