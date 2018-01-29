/*
 * data_pack.c
 *
 *  Created on: 2017��12��19��
 *      Author: yuwen
 */

#include "data_pack.h"



uint16_t brightness_set(uint8_t light_grade)
{
    switch(light_grade)
    {
    case '1':
        return BRIGHTNESS_LEVEL_1;
    case '2':
        return BRIGHTNESS_LEVEL_2;
    case '3':
        return BRIGHTNESS_LEVEL_3;
    case '4':
        return BRIGHTNESS_LEVEL_4;
    case '5':
        return BRIGHTNESS_LEVEL_5;
    case '6':
        return BRIGHTNESS_LEVEL_6;
    case '7':
        return BRIGHTNESS_LEVEL_7;
    case '8':
        return BRIGHTNESS_LEVEL_8;
    default:
        return BRIGHTNESS_LEVEL_8;
    }
}
//uint16_t IR_delay_level_set(uint8_t delay_level, uint8_t blink_level)
//{
//    if(blink_level == '2')
//        return delay_level;
//    else if(blink_level == '3')
//        return 2*delay_level;
//    else if(blink_level == '4')
//        return 4*delay_level;
//    else
//        return delay_level;
//}

uint16_t IR_delay_level_set(uint32_t speed, uint8_t blink_level)
{
    switch(blink_level)
    {
    case '2':
        if(speed < 4000000)
            return 8;
        else
            return 12;
    case '3':
        if(speed < 4000000)
            return 16;
        else
            return 24;
    case '4':
        if(speed < 4000000)
            return 32;
        else
            return 48;
    default:
        if(speed < 4000000)
            return 8;
        else
            return 12;
    }
}

uint16_t blink_level_set(uint8_t blink_freq)
{
    switch(blink_freq)
    {
    case '1':
        return BLINK_LEVEL_1;
    case '2':
        return BLINK_LEVEL_2;
    case '3':
        return BLINK_LEVEL_3;
    case '4':
        return BLINK_LEVEL_4;
    default:
        return BLINK_LEVEL_2;
    }
}

uint8_t blink_30time_judge(uint8_t blink_freq)
{
    if(blink_freq == '2')
        return 1;
    else
        return 0;
}
