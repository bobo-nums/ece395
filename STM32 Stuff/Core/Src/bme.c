/*
 * bme.c
 *
 *  Created on: Nov 23, 2021
 *      Author: bobox
 */

#include "bme.h"

uint32_t BME_read24(SPI_HandleTypeDef* spi, uint8_t addr){
    uint8_t buf[3];
    addr = (uint8_t)(addr | 0x80);
    HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi, &addr, 1, 100);
    HAL_SPI_Receive(spi, buf, 3, 100);
    HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_SET);
    return (uint32_t)(buf[0]) << 16 | (uint32_t)(buf[1]) << 8 | (uint32_t)(buf[2]);
}

float BME_readTemperature(SPI_HandleTypeDef* spi) {
  int32_t var1, var2;

  int32_t adc_T = BME_read24(spi, BME280_REGISTER_TEMPDATA);
  if (adc_T == 0x800000) // value in case temp measurement was disabled
    return -1;
  adc_T >>= 4;

  var1 = (int32_t)((adc_T / 8) - ((int32_t)_bme280_calib.dig_T1 * 2));
  var1 = (var1 * ((int32_t)_bme280_calib.dig_T2)) / 2048;
  var2 = (int32_t)((adc_T / 16) - ((int32_t)_bme280_calib.dig_T1));
  var2 = (((var2 * var2) / 4096) * ((int32_t)_bme280_calib.dig_T3)) / 16384;

  t_fine = var1 + var2;

  int32_t T = (t_fine * 5 + 128) / 256;

  return (float)T / 100;
}