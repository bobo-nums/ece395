/*
 * ina239.h
 *
 *  Created on: Sep 30, 2021
 *      Author: bobox
 */

#ifndef INC_INA239_H_
#define INC_INA239_H_

#include "stm32f4xx_hal_spi.h"

// INA239-Q1 Registers
#define CONFIG 			0x0
#define ADC_CONFIG 		0x1
#define SHUNT_CAL 		0x2
#define VSHUNT 			0x4
#define VBUS 			0x5
#define DIETEMP 		0x6
#define CURRENT 		0x7
#define POWER 			0x8	// power register size 24 bits, rest 16
#define DIAG_ALRT		0xB
#define SOVL 			0xC
#define SUVL 			0xD
#define BOVL 			0xE
#define BUVL 			0xF
#define TEMP_LIMIT 		0x10
#define PWR_LIMIT 		0x11
#define MANUFACTURER_ID 0x3E
#define DEVICE_ID 		0x3F

// Access type codes
#define INA_READ		1
#define INA_WRITE		0

void INA_SPI_init(void);
void INA_SPI_write(uint8_t addr, uint16_t* buf);
void INA_SPI_read(uint8_t addr, uint32_t* buf, uint32_t count);

#endif /* INC_INA239_H_ */
