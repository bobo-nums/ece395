/*
 * sd.c
 *
 *  Created on: Oct 17, 2021
 *      Author: bobox
 */

#include "sd.h"

void SD_mount(FATFS *FatFs){
	FRESULT fres;	// result after operations
    while (HAL_GPIO_ReadPin(SD_DET_GPIO_Port, SD_DET_Pin) != GPIO_PIN_SET){
		myprintf("waiting to init");
        HAL_Delay(1000);
    }
    HAL_Delay(1000);	// short delay to let SD card settle

    // Open the file system
    fres = f_mount(FatFs, "", 1); // 1=mount now
    if (fres != FR_OK){
        myprintf("f_mount error (%i)\r\n", fres);
        while(1);
    }
}

UINT SD_write(const TCHAR* path, BYTE mode, const char* buf, UINT btw){
    FIL fil;					// file handle
	FRESULT fres; 				// result after operations
	UINT bytesWrote;
	
	fres = f_open(&fil, path, mode);
	if(fres != FR_OK){
		myprintf("f_open error (%i)\r\n", fres);
		while(1);
	}

	fres = f_write(&fil, buf, btw, &bytesWrote);
	if(fres != FR_OK) {
		myprintf("f_write error (%i)\r\n", fres);
	}

	f_close(&fil);				// close file

	return bytesWrote;
}

void SD_unmount(){
	f_mount(NULL, "", 0);
	myprintf("unmounted");
}