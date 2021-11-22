/*
 * hall.h
 *
 *  Created on: Oct 24, 2021
 *      Author: bobox
 */

#ifndef INC_HALL_H_
#define INC_HALL_H_

#include "main.h"

// start bytes
#define START_B_0 0xAA
#define START_B_1 0xFF

void HALL_read(SPI_HandleTypeDef* spi, uint8_t* buf);

#endif /* INC_HALL_H_ */
