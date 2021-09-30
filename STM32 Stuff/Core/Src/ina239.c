/*
 * ina239.c
 *
 *  Created on: Sep 30, 2021
 *      Author: bobox
 */

#include "ina239.h"
#include "main.h"

void INA_SPI_init();

void INA_SPI_write(uint8_t addr, uint16_t* buf){
	uint8_t data[3];
	data[0] = (addr << 2) | INA_WRITE;									// format 1st byte (addr)
	data[1] = (uint8_t)(buf >> 8);										// format 2nd byte (buf)
	data[2] = (uint8_t)buf;												// format 3rd byte (buf)
	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
	HAL_SPI_Transmit(&hspi2, (uint8_t*)data, 3, 100);					// send 3 byte data packet
	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high
}

void INA_SPI_read(uint8_t addr, uint32_t* buf, uint32_t count){
	uint8_t data[count];
	addr = (addr << 2) | INA_READ;										// format 1st byte
	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
	HAL_SPI_Transmit(&hspi2, (uint8_t*)addr, 1, 100);					// send 1st byte
	HAL_SPI_Receive(&hspi2, data, count, 100);							// receive data
	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high

}
