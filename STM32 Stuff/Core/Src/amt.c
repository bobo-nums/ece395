/*
 * amt.c
 *
 *  Created on: Nov 30, 2021
 *      Author: bobox
 */

#include "amt.h"

uint8_t AMT_RW(SPI_HandleTypeDef* spi, uint8_t addr){
    uint8_t data;
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_RESET);
    // HAL_SPI_Transmit(spi, &addr, 1, 100);
    HAL_SPI_TransmitReceive(spi, addr, data, 1, 100);
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_SET);
}

uint16_t AMT_getPos(SPI_HandleTypeDef* spi, uint8_t res){
    uint16_t currentPos;
    bool binArr[16];
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(spi, AMT_NOP, currentPos, 2, 100);
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_SET);
    for(int i = 0; i < 16; i++){
        binArr[i] = (0x01) & (currentPos >> (i));
    }
    if((binArr[15] == !(binArr[13] ^ binArr[11] ^ binArr[9] ^ binArr[7] ^ binArr[5] ^ binArr[3] ^ binArr[1]))
          && (binArr[14] == !(binArr[12] ^ binArr[10] ^ binArr[8] ^ binArr[6] ^ binArr[4] ^ binArr[2] ^ binArr[0]))){
        //we got back a good position, so just mask away the checkbits
        currentPos &= 0x3FFF;
    }
    else{
        currentPos = 0xFFFF; //bad position
    }
    //If the resolution is 12-bits, and wasn't 0xFFFF, then shift position, otherwise do nothing
    if ((res == RES12) && (currentPos != 0xFFFF)){
        currentPos = currentPos >> 2;
    }
  return currentPos;
}

void AMT_setZero(SPI_HandleTypeDef* spi){
    uint8_t buf[2];
    buf[1] = AMT_NOP;
    buf[0] = AMT_ZERO;
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi, buf, 2, 100); // might need 3us delay??
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_SET);
    HAL_Delay(250); // 250 ms delay to allow the encoder to reset
}

void AMT_reset(SPI_HandleTypeDef* spi){
    uint8_t buf[2];
    buf[1] = AMT_NOP;
    buf[0] = AMT_RESET;
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi, buf, 2, 100); // might need 3us delay??
    HAL_GPIO_WritePin(AMT_CS_GPIO_Port, AMT_CS_Pin, GPIO_PIN_SET);
    HAL_Delay(250); // 250 ms delay to allow the encoder to start back up
}