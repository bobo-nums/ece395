/*
 * bme.c
 *
 *  Created on: Nov 23, 2021
 *      Author: bobox
 */

#include "bme.h"

bool BME_init(SPI_HandleTypeDef* spi){
  if(BME_read8(spi, BME280_REGISTER_CHIPID) != 0x60){
    return false;
  }
  BME_write8(spi, BME280_REGISTER_SOFTRESET, 0xB6);
  HAL_Delay(10);
  while(isReadingCalibration(spi)){
    HAL_Delay(10);
  }
  readCoefficients(spi);
  setSampling(spi);
  HAL_Delay(100);
  return true;
}

void BME_write8(SPI_HandleTypeDef* spi, uint8_t addr, uint8_t val){
  uint8_t buf[2];
  buf[0] = addr & ~0x80;
  buf[1] = val;
  HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(spi, &buf, 2, 100);
  HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_SET);
}

bool isReadingCalibration(SPI_HandleTypeDef* spi){
  uint8_t const rStatus = BME_read8(spi, BME280_REGISTER_STATUS);
  return (rStatus & (1 << 0)) != 0;
}

void readCoefficients(SPI_HandleTypeDef* spi){
  _bme280_calib.dig_T1 = BME_read16_LE(spi, BME280_REGISTER_DIG_T1);
  _bme280_calib.dig_T2 = BME_readS16_LE(spi, BME280_REGISTER_DIG_T2);
  _bme280_calib.dig_T3 = BME_readS16_LE(spi, BME280_REGISTER_DIG_T3);
}

void setSampling(SPI_HandleTypeDef* spi){
  BME_write8(spi, BME280_REGISTER_CONTROL, MODE_SLEEP);
  BME_write8(spi, BME280_REGISTER_CONTROLHUMID, SAMPLING_X16);
  BME_write8(spi, BME280_REGISTER_CONFIG, (STANDBY_MS_0_5 << 5) | (FILTER_OFF << 2) | 0);
  BME_write8(spi, BME280_REGISTER_CONTROL, (SAMPLING_X16 << 5) | (SAMPLING_X16 << 2) | MODE_NORMAL);
}

uint16_t BME_read16_LE(SPI_HandleTypeDef* spi, uint8_t addr){
  uint16_t temp = BME_read16(spi, addr);
  return (temp >> 8) | (temp << 8);
}

int16_t BME_readS16_LE(SPI_HandleTypeDef* spi, uint8_t addr){
  return (int16_t)BME_read16_LE(spi, addr);
}

uint8_t BME_read8(SPI_HandleTypeDef* spi, uint8_t addr){
    uint8_t buf[1];
    addr = (uint8_t)(addr | 0x80);
    HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi, &addr, 1, 100);
    HAL_SPI_Receive(spi, buf, 1, 100);
    HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_SET);
    return buf[0];
}

uint16_t BME_read16(SPI_HandleTypeDef* spi, uint8_t addr){
  uint8_t buf[2];
  addr = (uint8_t)(addr | 0x80);
  HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(spi, &addr, 1, 100);
  HAL_SPI_Receive(spi, buf, 3, 100);
  HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_SET);
  return (uint16_t)(buf[0]) << 8 | (uint16_t)(buf[1]);
}

uint32_t BME_read24(SPI_HandleTypeDef* spi, uint8_t addr){
    uint8_t buf[3];
    addr = (uint8_t)(addr | 0x80);
    HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi, &addr, 1, 100);
    HAL_SPI_Receive(spi, buf, 3, 100);
    HAL_GPIO_WritePin(BME_CS_GPIO_Port, BME_CS_Pin, GPIO_PIN_SET);
    return (uint32_t)buf[0] << 16 | (uint32_t)buf[1] << 8 | (uint32_t)buf[2];
}

float BME_readTemperature(SPI_HandleTypeDef* spi) {
  int32_t var1, var2;

  int32_t adc_T = BME_read24(spi, BME280_REGISTER_TEMPDATA);
  if (adc_T == 0x800000){ // value in case temp measurement was disabled
    return -1;
  }
  adc_T >>= 4;

  var1 = (int32_t)((adc_T / 8) - ((int32_t)_bme280_calib.dig_T1 * 2));
  var1 = (var1 * ((int32_t)_bme280_calib.dig_T2)) / 2048;
  var2 = (int32_t)((adc_T / 16) - ((int32_t)_bme280_calib.dig_T1));
  var2 = (((var2 * var2) / 4096) * ((int32_t)_bme280_calib.dig_T3)) / 16384;

  int32_t t_fine = var1 + var2;

  int32_t T = (t_fine * 5 + 128) / 256;

  return (float)T / 100;
}