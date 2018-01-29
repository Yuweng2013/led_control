/*
 * rs485.h
 *
 *  Created on: 2017Äê11ÔÂ18ÈÕ
 *      Author: yuwen
 */

#ifndef RS485_H_
#define RS485_H_

#include "driverlib.h"
//*****************************************************************************
//
//Select Baud rate
//
//*****************************************************************************
#define BAUD_RATE                               9600
//*****************************************************************************


extern void usci_A_uart_initial();

extern void set_rs485_as_driver();
extern void set_rs485_as_receiver();

extern void rs485_data_package_sent(uint8_t R_data[20],uint8_t i);


#endif /* RS485_H_ */
