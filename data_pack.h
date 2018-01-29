/*
 * data_pack.h
 *
 *  Created on: 2017��12��19��
 *      Author: yuwen
 */

#ifndef DATA_PACK_H_
#define DATA_PACK_H_


#include "driverlib.h"

/*
 * The clock of the SMCLK is 1.048MHz, so the dimming  frequency of LED is determined
 * by LED_TIMER_PERIOD on 2kHz and the brightness is decided by the duty cycle of timerB
 * according to the brightness_level variable.
 */
#define LED_TIMER_PERIOD    3200
#define BRIGHTNESS_LEVEL_1  3000     //100%
#define BRIGHTNESS_LEVEL_2  2560     //80%
#define BRIGHTNESS_LEVEL_3  2080     //65%
#define BRIGHTNESS_LEVEL_4  1600     //50%
#define BRIGHTNESS_LEVEL_5  1120     //35%
#define BRIGHTNESS_LEVEL_6  800     //25%
#define BRIGHTNESS_LEVEL_7  320      //10%
#define BRIGHTNESS_LEVEL_8  160      //5%
/*
 * Blink level is set by the delay time of ms to distinguish the the different frequency
 */
#define BLINK_LEVEL_1 32768          //  15time/min
#define BLINK_LEVEL_2 32768          //  30time/min
#define BLINK_LEVEL_3 16384           //  60time/min
#define BLINK_LEVEL_4 8192           //  120time/min

#define IR_DELAY_LEVEL_1 40
#define IR_DELAY_LEVEL_2 20
#define IR_DELAY_LEVEL_3 10
#define IR_DELAY_LEVEL_4 5

extern uint16_t brightness_set(uint8_t light_grade);
extern uint16_t blink_level_set(uint8_t blink_freq);
extern uint8_t blink_30time_judge(uint8_t blink_freq);
extern uint16_t IR_delay_level_set(uint32_t speed, uint8_t blink_level);


#endif /* DATA_PACK_H_ */
