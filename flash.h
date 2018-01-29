/*
 * flash.h
 *
 *  Created on: 2017Äê12ÔÂ21ÈÕ
 *      Author: yuwen
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "driverlib.h"

//*****************************************************************************
//
//INFOB address in flash into which calibration data would be written
//
//*****************************************************************************
#define INFOB_START   (0x1900)

extern char ReadSegment_256(char index);
extern void WriteSegment(uint8_t *calibration_data_char, uint8_t count);
//extern void FlashRead_InfoB(char *Dataout,uint8_t count);

#endif /* FLASH_H_ */
