/*
 * trik_hmc5883l.h
 *
 *  Created on: Fabruary 6, 2015
 *      Author: Rostislav Varzar
 */

#ifndef TRIK_HMC5883L_H_
#define TRIK_HMC5883L_H_

void HMC5883L_init();
uint16_t HMC5883L_readX();
uint16_t HMC5883L_readY();
uint16_t HMC5883L_readZ();

#endif /* TRIK_HMC5883L_H_ */
