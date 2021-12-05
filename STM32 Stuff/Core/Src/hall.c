/*
 * hall.c
 *
 *  Created on: Oct 24, 2021
 *      Author: bobox
 */

#include "hall.h"

void HALL_read(SPI_HandleTypeDef* spi, uint8_t* buf) {
	// format data bytes
	uint8_t data[2];
	data[0] = START_B_0;
	data[1] = START_B_1;

	HAL_GPIO_WritePin(HALL_CS_GPIO_Port, HALL_CS_Pin, GPIO_PIN_RESET);	// pull CS low
	HAL_SPI_Transmit(spi, &data, 2, 100);					        	// send 2 bytes
    HAL_SPI_Receive(spi, buf, 4, 100);                                  // receieve 2 data bytes + 2 inverted data bytes
	HAL_GPIO_WritePin(HALL_CS_GPIO_Port, HALL_CS_Pin, GPIO_PIN_SET);	// pull CS high
}
