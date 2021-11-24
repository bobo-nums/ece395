/*
 * bme.h
 *
 *  Created on: Nov 23, 2021
 *      Author: bobox
 */

#ifndef INC_BME_H_
#define INC_BME_H_

#include "main.h"
#include "stm32f4xx_hal.h"

/*!
 *  @brief Register addresses
 */
enum {
  BME280_REGISTER_DIG_T1 = 0x88,
  BME280_REGISTER_DIG_T2 = 0x8A,
  BME280_REGISTER_DIG_T3 = 0x8C,

  BME280_REGISTER_DIG_P1 = 0x8E,
  BME280_REGISTER_DIG_P2 = 0x90,
  BME280_REGISTER_DIG_P3 = 0x92,
  BME280_REGISTER_DIG_P4 = 0x94,
  BME280_REGISTER_DIG_P5 = 0x96,
  BME280_REGISTER_DIG_P6 = 0x98,
  BME280_REGISTER_DIG_P7 = 0x9A,
  BME280_REGISTER_DIG_P8 = 0x9C,
  BME280_REGISTER_DIG_P9 = 0x9E,

  BME280_REGISTER_DIG_H1 = 0xA1,
  BME280_REGISTER_DIG_H2 = 0xE1,
  BME280_REGISTER_DIG_H3 = 0xE3,
  BME280_REGISTER_DIG_H4 = 0xE4,
  BME280_REGISTER_DIG_H5 = 0xE5,
  BME280_REGISTER_DIG_H6 = 0xE7,

  BME280_REGISTER_CHIPID = 0xD0,
  BME280_REGISTER_VERSION = 0xD1,
  BME280_REGISTER_SOFTRESET = 0xE0,

  BME280_REGISTER_CAL26 = 0xE1, // R calibration stored in 0xE1-0xF0

  BME280_REGISTER_CONTROLHUMID = 0xF2,
  BME280_REGISTER_STATUS = 0XF3,
  BME280_REGISTER_CONTROL = 0xF4,
  BME280_REGISTER_CONFIG = 0xF5,
  BME280_REGISTER_PRESSUREDATA = 0xF7,
  BME280_REGISTER_TEMPDATA = 0xFA,
  BME280_REGISTER_HUMIDDATA = 0xFD
};

/**************************************************************************/
/*!
    @brief  calibration data
*/
/**************************************************************************/
typedef struct {
  uint16_t dig_T1; ///< temperature compensation value
  int16_t dig_T2;  ///< temperature compensation value
  int16_t dig_T3;  ///< temperature compensation value

  uint16_t dig_P1; ///< pressure compensation value
  int16_t dig_P2;  ///< pressure compensation value
  int16_t dig_P3;  ///< pressure compensation value
  int16_t dig_P4;  ///< pressure compensation value
  int16_t dig_P5;  ///< pressure compensation value
  int16_t dig_P6;  ///< pressure compensation value
  int16_t dig_P7;  ///< pressure compensation value
  int16_t dig_P8;  ///< pressure compensation value
  int16_t dig_P9;  ///< pressure compensation value

  uint8_t dig_H1; ///< humidity compensation value
  int16_t dig_H2; ///< humidity compensation value
  uint8_t dig_H3; ///< humidity compensation value
  int16_t dig_H4; ///< humidity compensation value
  int16_t dig_H5; ///< humidity compensation value
  int8_t dig_H6;  ///< humidity compensation value
} bme280_calib_data;
// /*=========================================================================*/


  /**************************************************************************/
  /*!
      @brief  sampling rates
  */
  /**************************************************************************/
  enum sensor_sampling {
    SAMPLING_NONE = 0b000,
    SAMPLING_X1 = 0b001,
    SAMPLING_X2 = 0b010,
    SAMPLING_X4 = 0b011,
    SAMPLING_X8 = 0b100,
    SAMPLING_X16 = 0b101
  };

  /**************************************************************************/
  /*!
      @brief  power modes
  */
  /**************************************************************************/
  enum sensor_mode {
    MODE_SLEEP = 0b00,
    MODE_FORCED = 0b01,
    MODE_NORMAL = 0b11
  };

  /**************************************************************************/
  /*!
      @brief  filter values
  */
  /**************************************************************************/
  enum sensor_filter {
    FILTER_OFF = 0b000,
    FILTER_X2 = 0b001,
    FILTER_X4 = 0b010,
    FILTER_X8 = 0b011,
    FILTER_X16 = 0b100
  };

  /**************************************************************************/
  /*!
      @brief  standby duration in ms
  */
  /**************************************************************************/
  enum standby_duration {
    STANDBY_MS_0_5 = 0b000,
    STANDBY_MS_10 = 0b110,
    STANDBY_MS_20 = 0b111,
    STANDBY_MS_62_5 = 0b001,
    STANDBY_MS_125 = 0b010,
    STANDBY_MS_250 = 0b011,
    STANDBY_MS_500 = 0b100,
    STANDBY_MS_1000 = 0b101
  };


bme280_calib_data _bme280_calib; //!< here calibration data is stored

bool BME_init(SPI_HandleTypeDef* spi);
void BME_write8(SPI_HandleTypeDef* spi, uint8_t addr, uint8_t val);
bool isReadingCalibration(SPI_HandleTypeDef* spi);
void readCoefficients(SPI_HandleTypeDef* spi);
void setSampling(SPI_HandleTypeDef* spi);
uint16_t BME_read16_LE(SPI_HandleTypeDef* spi, uint8_t addr);
int16_t BME_readS16_LE(SPI_HandleTypeDef* spi, uint8_t addr);

uint8_t BME_read8(SPI_HandleTypeDef* spi, uint8_t addr);
uint16_t BME_read16(SPI_HandleTypeDef* spi, uint8_t addr);
uint32_t BME_read24(SPI_HandleTypeDef* spi, uint8_t addr);
float BME_readTemperature(SPI_HandleTypeDef* spi);

#endif /* INC_BME_H_ */
