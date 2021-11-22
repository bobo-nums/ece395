/*
 * rtc.c
 *
 *  Created on: Oct 19, 2021
 *      Author: bobox
 */

#include "rtc.h"

void rtc_set_time(RTC_HandleTypeDef* hrtc) {
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    sTime.Hours = 0x00;    // set hours
    sTime.Minutes = 0x00;  // set minutes
    sTime.Seconds = 0x00;  // set seconds
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }
    sDate.WeekDay = RTC_WEEKDAY_MONDAY;  // day
    sDate.Month = RTC_MONTH_JANUARY;     // month
    sDate.Date = 0x00;                   // date
    sDate.Year = 0x00;                   // year
    if (HAL_RTC_SetDate(hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }
    HAL_RTCEx_BKUPWrite(hrtc, RTC_BKP_DR1, 0x0000);  // backup register
}

void rtc_get_time(RTC_HandleTypeDef* hrtc, RTC_DateTypeDef* date, RTC_TimeTypeDef* time) {
    /* Get the RTC current Time */
    HAL_RTC_GetTime(hrtc, time, RTC_FORMAT_BIN);
    /* Get the RTC current Date */
    HAL_RTC_GetDate(hrtc, date, RTC_FORMAT_BIN);   
}