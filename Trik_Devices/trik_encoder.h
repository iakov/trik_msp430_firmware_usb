/*
 * trik_encoder.h
 *
 *  Created on: November 7, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_ENCODER_H_
#define TRIK_ENCODER_H_

//Registers
#define EECTL               0x00
#define EEVAL               0x01
#define EESTA               0x02

//Encoder errors
#define ENC_NO_ERROR        0x00

//Max encoders
#define MAX_ENCODERS        0x04

//Masks for bits of control register
#define ENC_ENABLE          0x8000 //Enable bit
#define ENC_ASYNC           0x4000 //Async mode
#define ENC_2WIRES          0x2000 //2-wires mode
#define ENC_PUPEN           0x1000 //Pull up resistors
#define ENC_FALL            0x0800 //Falling edge select

//Prototypes for the APIs
void ENCODER_handler(uint8_t ENC_NUMBER);
void ENCODER_enableController(uint8_t ENC_NUMBER);
void ENCODER_disableController(uint8_t ENC_NUMBER);

//Encoder registers
struct tEncoderRegisters
{
    uint16_t ECTL;
    uint32_t EVAL;
    uint16_t ESTA;
};

//Encoder registers array
volatile struct tEncoderRegisters ENC[MAX_ENCODERS];

#endif /* TRIK_ENCODER_H_ */
