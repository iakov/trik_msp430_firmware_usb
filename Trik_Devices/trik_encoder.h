/*
 * trik_encoder.h
 *
 *  Created on: November 7, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_ENCODER_H_
#define TRIK_ENCODER_H_

//Configuration parameters
#define DISABLE             0
#define ENABLE              1

//Prototypes for the APIs
uint8_t ENCODER_hadler(uint8_t ENC_NUMBER);
void ENCODER_enableController(uint8_t ENC_NUMBER);
void ENCODER_disableController(uint8_t ENC_NUMBER);
uint32_t ENCODER_getEncoderValue(uint8_t ENC_NUMBER);

//Max encoders
#define MAX_ENCODERS 4

//Encoder registers
struct tEncoderRegisters
{
    uint16_t ECTL;
    uint16_t EFRQ;
    uint32_t EVAL;
    uint16_t ESTA;
    uint8_t ENC_EN;
};

//Encoder registers array
struct tEncoderRegisters ENC[MAX_ENCODERS];

#endif /* TRIK_ENCODER_H_ */
