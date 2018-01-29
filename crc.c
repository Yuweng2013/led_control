/*
 * crc.c
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: yuwen
 */

#include "crc.h"



void CRC_8(uint8_t *buf, uint8_t len, uint8_t *crc_out)
{
    uint8_t crc_reg = 0x00;
    int j;
    while(len--)
    {
        crc_reg ^= *buf++;
        for(j=0;j<8;j++)
        {
            if (crc_reg & 0x80)
                crc_reg = (crc_reg << 1) ^ 0x31;
            else
                crc_reg = (crc_reg << 1);
        }
    }
    *crc_out=crc_reg;
}
