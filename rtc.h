/*
 * rtc.h
 *
 *  Created on: 2017��12��26��
 *      Author: yuwen
 */

#ifndef RTC_H_
#define RTC_H_

#include "driverlib.h"

//*****************************************************************************
//
//Target frequency for MCLK in kHz
//
//*****************************************************************************
#define UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ   8000

//*****************************************************************************
//
//MCLK/FLLRef Ratio
//
//*****************************************************************************
#define UCS_MCLK_FLLREF_RATIO   244

extern void rtc_clock_initial();
extern void DCO_set_to_8MHz();


extern void current_time_initial_set(uint8_t *ptr);

extern void state_time_alarm_set();

void rtc_interrupt_initial();


#endif /* RTC_H_ */
