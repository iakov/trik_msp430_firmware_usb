/*
 * trik_encoder.h
 *
 *  Created on: November 7, 2014
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_ENCODER_H_
#define TRIK_ENCODER_H_

//Max motors
#define MAX_ENCODERS 4

//Motor registers
struct tEncoderRegisters
{
    uint16_t MCTL;
    uint16_t MPWR;
    uint16_t MFRQ;
    uint16_t MANG;
    uint16_t MTMR;
    uint32_t MVAL;
    uint16_t MSTA;
    uint8_t MOT_EN;
    uint8_t MOT_PWR;
    uint8_t MOT_DIR;
    uint8_t MOT_BRK;
};

//Motors registers array
struct tEncoderRegisters ENC[MAX_ENCODERS];

#endif /* TRIK_ENCODER_H_ */
