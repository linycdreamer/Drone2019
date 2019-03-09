#ifndef __DSHOT_H__
#define __DSHOT_H__
#include "stm32f10x.h"
#define TIMPeriod 30 
#define ESC_BIT_0     11
#define ESC_BIT_1     22
#define ESC_CMD_BUFFER_LEN 18

void setDshotValue(uint16_t setValue);
#endif // __DSHOT_H__
