#ifndef __ZEROCHECKTASK_H__
#define __ZEROCHECKTASK_H__
#include "stm32f10x.h"

#define pluckBulletHeader  1
typedef struct 
{
	uint8_t header;
	float   Circle;           //ת��Ȧ��
	float   CountCycle;       //ת��һȦ���ܼ�������
	float   LastValue;        //����������һ�ε�ֵ	
	float   ActualValue;      //����������ǰֵ
	float   PreError;         //������жϲ�ֵ
}ZeroCheck_Typedef;

float Get_ZeroCheck_Value_Interface(ZeroCheck_Typedef *zero,float value);
void ZeroCheck_Init_Interface(ZeroCheck_Typedef *zeroCheck,float CountCycle);
float ZeroCheck_cal(ZeroCheck_Typedef *Zero,float value);
void ZeroCheck_Init(ZeroCheck_Typedef *zero);
float ResetZeroCheck(ZeroCheck_Typedef *zeroCheck);
#endif
