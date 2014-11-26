/*
 * trik_encoder.h
 *
 *  Created on: November 7, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_ENCODER_H_
#define TRIK_ENCODER_H_

//Configuration parameters
#define DISABLE 0
#define ENABLE  1

//Registers
#define EECTL 0x00
#define EEVAL 0x01
#define EESTA 0x02

//Encoder types
#define WIRE1 0
#define WIRE2 1

//Encoder edge
#define RIS_EDGE 0
#define FAL_EDGE 1

//Encoder errors
#define ENC_NO_ERROR 0x00

//Prototypes for the APIs
void ENCODER_hadler(uint8_t ENC_NUMBER);
void ENCODER_enableController(uint8_t ENC_NUMBER);
void ENCODER_disableController(uint8_t ENC_NUMBER);
//void ENCODER_enablePullup(uint8_t ENC_NUMBER);
//void ENCODER_disablePullup(uint8_t ENC_NUMBER);
//void ENCODER_fallingEdge(uint8_t ENC_NUMBER);
//void ENCODER_risingEdge(uint8_t ENC_NUMBER);

//Max encoders
#define MAX_ENCODERS 4

//Encoder registers
struct tEncoderRegisters
{
    uint16_t ECTL;
    uint32_t EVAL;
    uint16_t ESTA;
    uint8_t ENC_EN;
    uint8_t ENC_PUP;
    uint8_t ENC_MOD;
    uint8_t ENC_TYP;
    uint8_t ENC_EDG;
};

//Encoder registers array
volatile struct tEncoderRegisters ENC[MAX_ENCODERS];

#endif /* TRIK_ENCODER_H_ */
