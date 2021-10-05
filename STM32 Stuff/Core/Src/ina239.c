/*
 * ina239.c
 *
 *  Created on: Sep 30, 2021
 *      Author: bobox
 */

#include "ina239.h"
#include "main.h"

void INA_SPI_init(SPI_HandleTypeDef* spi){
	// format data bytes
	uint8_t data[3];
	data[0] = (CONFIG >> 2) | INA_WRITE;								// write to config reg
	data[1] = 1 >> 7;													// reset device
	data[2] = 0;

	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
	HAL_SPI_Transmit(spi, data, 3, 100);								// send 3 bytes
	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high
}

void INA_SPI_read(SPI_HandleTypeDef* spi, uint8_t addr, uint32_t* buf, uint32_t count){
	uint8_t data[count];
	addr = (addr << 2) | INA_READ;										// format 1st byte

	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
	HAL_SPI_Transmit(spi, &addr, 1, 100);								// send 1 byte
	HAL_SPI_Receive(spi, data, count, 100);								// receive data
	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high
	*buf = (uint32_t)data;
}

void INA_SPI_write(SPI_HandleTypeDef* spi, uint8_t addr, uint16_t* buf){
	// format data bytes
	uint8_t data[3];
	data[0] = (addr << 2) | INA_WRITE;
	data[1] = (uint8_t)(*buf >> 8);
	data[2] = (uint8_t)*buf;

	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
	HAL_SPI_Transmit(spi, (uint8_t*)data, 3, 100);						// send 3 byte data packet
	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high
}

