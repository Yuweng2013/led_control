/*
 * led.h
 *
 *  Created on: 2017��11��9��
 *      Author: yuwen
 */

#ifndef LED_H_
#define LED_H_

#include "driverlib.h"

#define CPU_F ((double)1000000)
//��ʱ�ӵ�Ƶ��1MHz
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
//__delay_cycles()��ʱ����Ϊϵͳ�Դ��⺯��
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

extern void delay(uint16_t ms);

extern void timer_b_initial(uint16_t TIMER_PERIOD);

void led1_brightness_level_set(uint16_t brightness_level);
void led2_brightness_level_set(uint16_t brightness_level);


extern void led_enable(uint8_t flag);

extern void led1_blink(uint16_t freq1_blink);
extern void led2_blink(uint16_t freq2_blink);

extern void led1_stop();
extern void led2_stop();

extern void led1_shinning();
extern void led2_shinning();

extern void timer_A2_initial();
extern void led_blink_freq(uint16_t freq);

#endif /* LED_H_ */
