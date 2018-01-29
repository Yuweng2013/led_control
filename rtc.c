/*
 * rtc.c
 *
 *  Created on: 2017��12��26��
 *      Author: yuwen
 */


#include "rtc.h"

void rtc_clock_initial()
{
    // Select XT1
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P5,
        GPIO_PIN4 + GPIO_PIN5
        );

    //Initialize LFXT1
    UCS_turnOnLFXT1(UCS_XT1_DRIVE_3,
                    UCS_XCAP_3
                    );

    //Set ACLK = LFXT1
    UCS_initClockSignal(
        UCS_ACLK,
        UCS_XT1CLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );
}

void DCO_set_to_8MHz()
{
    //Set VCore = 1 for 8MHz clock
    PMM_setVCore(PMM_CORE_LEVEL_1);

    //Set DCO FLL reference = XT1CLK
    UCS_initClockSignal(
        UCS_FLLREF,
        UCS_XT1CLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );

    //Set Ratio and Desired MCLK Frequency  and initialize DCO
    UCS_initFLLSettle(
        UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ,
        UCS_MCLK_FLLREF_RATIO
        );


}

void current_time_initial_set(uint8_t *ptr)
{
    Calendar currentTime;
    //Setup Current Time for Calendar
    currentTime.Seconds = *(ptr + 11);
    currentTime.Minutes = *(ptr + 10);
    currentTime.Hours = *(ptr + 9);
    currentTime.DayOfWeek = *(ptr + 8);
    currentTime.DayOfMonth = *(ptr + 7);
    currentTime.Month = *(ptr + 6);
    currentTime.Year = *(ptr + 5);

    //Initialize Calendar Mode of RTC
    /*
     * Base Address of the RTC_A_A
     * Pass in current time, intialized above
     * Use BCD as Calendar Register Format
     */
    RTC_A_initCalendar(RTC_A_BASE,
                       &currentTime,
                       RTC_A_FORMAT_BCD);
}

void state_time_alarm_set()
{
    //Setup Calendar Alarm for 5:00pm on the 5th day of the week.
    //Note: Does not specify day of the week.
    RTC_A_configureCalendarAlarmParam param = {0};
    param.minutesAlarm = 0x00;
    param.hoursAlarm = 0x17;
    param.dayOfWeekAlarm = RTC_A_ALARMCONDITION_OFF;
    param.dayOfMonthAlarm = 0x05;

    RTC_A_configureCalendarAlarm(RTC_A_BASE, &param);
}

void rtc_interrupt_initial()
{
    //Specify an interrupt to assert every minute
    RTC_A_setCalendarEvent(RTC_A_BASE,
                           RTC_A_CALENDAREVENT_MINUTECHANGE);

    //Enable interrupt for RTC Ready Status, which asserts when the RTC
    //Calendar registers are ready to read.
    //Also, enable interrupts for the Calendar alarm and Calendar event.
    RTC_A_clearInterrupt(RTC_A_BASE,
                         RTCRDYIFG + RTCTEVIFG + RTCAIFG);
    RTC_A_enableInterrupt(RTC_A_BASE,
                          RTCRDYIE + RTCTEVIE + RTCAIE);
}
