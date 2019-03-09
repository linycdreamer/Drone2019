#ifndef __DM50_H__
#define __DM50_H__
#include "stm32f10x.h"
struct DM50
{
	uint8_t id;
	uint32_t sendId;
	uint32_t receiveId;
	uint32_t sendMax;
};
#endif // __DM50_H__
