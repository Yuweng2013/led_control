/*
 * flash.c
 *
 *  Created on: 2017Äê12ÔÂ21ÈÕ
 *      Author: yuwen
 */




#include "flash.h"

char ReadSegment_256(char index)
{
  char *flash_ptr = ((char *) INFOB_START) + index;
  return *flash_ptr;
}

//void FlashRead_InfoB(char *flash_ptr,uint8_t count)
//{
//    uint8_t i = 0;
////    for(i = 0; i< count; i++)
////    {
//    flash_ptr = ((char *) INFOB_START) + count;
////    }
//
//
//}

void WriteSegment(uint8_t *calibration_data_char, uint8_t count)
{
    uint16_t status;
    //Write calibration data to INFOB

    do
    {
        //Erase INFOB
        FlashCtl_eraseSegment((uint8_t *)INFOB_START);
        status = FlashCtl_performEraseCheck((uint8_t *)INFOB_START,
                                            128
                                            );
    }
    while(status == STATUS_FAIL);

    //Write calibration data to INFOB
    FlashCtl_write8(calibration_data_char,
                    (uint8_t *)INFOB_START,
                    count
                    );
}
