/*
 * rtc.h
 *
 *  Created on: Oct 19, 2021
 *      Author: bobox
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

void rtc_set_time(RTC_HandleTypeDef* hrtc);
void rtc_get_time(RTC_HandleTypeDef* hrtc, RTC_DateTypeDef* date, RTC_TimeTypeDef* time);

#endif /* INC_RTC_H_ */
