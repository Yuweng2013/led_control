/*
 * crc.h
 *
 *  Created on: 2018��1��25��
 *      Author: yuwen
 */

#ifndef CRC_H_
#define CRC_H_


#include <driverlib.h>

extern void CRC_8(uint8_t *buf, uint8_t len, uint8_t *crc_out);


#endif /* CRC_H_ */
