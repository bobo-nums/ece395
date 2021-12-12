///*
// * ina239.c
// *
// *  Created on: Sep 30, 2021
// *      Author: bobox
// */
//
//#include "ina239.h"
//
//void INA_init(SPI_HandleTypeDef* spi) {
//	// format data bytes
//	uint8_t data[3];
//	data[0] = (CONFIG >> 2) | INA_WRITE;								// write to config reg
//	data[1] = 0x80;														// reset device
//	data[2] = 0x00;
//
//	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
//	HAL_SPI_Transmit(spi, &data[0], sizeof(data), 100);					// send 3 bytes
//	while(HAL_SPI_GetState(spi) != HAL_SPI_STATE_READY);
//	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high
//}
//
//void INA_read(SPI_HandleTypeDef* spi, uint8_t addr, uint8_t* buf, uint32_t count) {
//	addr = (addr << 2) | INA_READ;										// format 1st byte
//	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
//	HAL_SPI_Transmit(spi, &addr, sizeof(addr), 100);					// send 1 byte
//	HAL_SPI_Receive(spi, buf, count, 100);								// receive data
//	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high
//}
//
//void INA_write(SPI_HandleTypeDef* spi, uint8_t addr, uint16_t* buf) {
//	// format data bytes
//	uint8_t data[3];
//	data[0] = (addr << 2) | INA_WRITE;
//	data[1] = (uint8_t)(*buf >> 8);
//	data[2] = (uint8_t)*buf;
//
//	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_RESET);	// pull CS low
//	HAL_SPI_Transmit(spi, &data[0], sizeof(data), 100);					// send 3 byte data packet
//	while(HAL_SPI_GetState(spi) != HAL_SPI_STATE_READY);
//	HAL_GPIO_WritePin(INA_CS_GPIO_Port, INA_CS_Pin, GPIO_PIN_SET);		// pull CS high
//}
//
