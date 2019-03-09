#ifndef __ZEROCHECKTASK_H__
#define __ZEROCHECKTASK_H__
#include "stm32f10x.h"

#define pluckBulletHeader  1
typedef struct 
{
	uint8_t header;
	float   Circle;           //转过圈数
	float   CountCycle;       //转过一圈的总计数周期
	float   LastValue;        //检测过零量上一次的值	
	float   ActualValue;      //检测过零量当前值
	float   PreError;         //检测量判断差值
}ZeroCheck_Typedef;

float Get_ZeroCheck_Value_Interface(ZeroCheck_Typedef *zero,float value);
void ZeroCheck_Init_Interface(ZeroCheck_Typedef *zeroCheck,float CountCycle);
float ZeroCheck_cal(ZeroCheck_Typedef *Zero,float value);
void ZeroCheck_Init(ZeroCheck_Typedef *zero);
float ResetZeroCheck(ZeroCheck_Typedef *zeroCheck);
#endif
