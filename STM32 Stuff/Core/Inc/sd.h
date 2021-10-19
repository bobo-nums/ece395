/*
 * sd.h
 *
 *  Created on: Oct 17, 2021
 *      Author: bobox
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "fatfs.h"
#include "ff.h"
#include "ina239.h"
#include "main.h"
#include "stm32f4xx_hal.h"

void SD_mount(FATFS *FatFs);
UINT SD_write(const TCHAR* path, BYTE mode, const char* buf, UINT btw);
void SD_unmount();

#endif /* INC_SD_H_ */
