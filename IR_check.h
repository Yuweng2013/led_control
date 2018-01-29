/*
 * IR_check.h
 *
 *  Created on: 2017Äê12ÔÂ11ÈÕ
 *      Author: yuwen
 */

#ifndef IR_CHECK_H_
#define IR_CHECK_H_


#include "driverlib.h"

extern void LDO_power_enable();

extern void IR_port_initial();

extern void timerA0_period_duty_cycle_set(uint16_t period, uint16_t duty_cycle);

extern void timerA1_capture_mode_initial();

#endif /* IR_CHECK_H_ */
