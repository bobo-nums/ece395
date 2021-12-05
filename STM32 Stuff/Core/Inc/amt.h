/*
 * amt.h
 *
 *  Created on: Nov 30, 2021
 *      Author: bobox
 */

#ifndef INC_AMT_H_
#define INC_AMT_H_

#include "main.h"
#include "stm32f4xx_hal.h"

#define AMT_NOP 0x00
#define AMT_RESET 0x60
#define AMT_ZERO 0x70

#define RES12 12
#define RES14 14

uint8_t AMT_RW(SPI_HandleTypeDef* spi, uint8_t addr);
uint16_t AMT_getPos(SPI_HandleTypeDef* spi, uint8_t resolution);
void AMT_setZero(SPI_HandleTypeDef* spi);
void AMT_reset(SPI_HandleTypeDef* spi);

#endif /* INC_AMT_H_ */
