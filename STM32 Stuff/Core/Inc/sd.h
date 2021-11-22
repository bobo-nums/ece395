/*
 * sd.h
 *
 *  Created on: Oct 17, 2021
 *      Author: bobox
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include "ff.h"
#include "main.h"

void SD_mount(FATFS* FatFs);
UINT SD_write(const TCHAR* path, BYTE mode, const char* buf, UINT btw);
void SD_unmount();

#endif /* INC_SD_H_ */
