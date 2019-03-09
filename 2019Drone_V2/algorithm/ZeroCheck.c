#include "ZeroCheck.h"

float Get_ZeroCheck_Value_Interface(ZeroCheck_Typedef *zero,float value)
{
		return ZeroCheck_cal(zero,value);//����datareceive�Ľӿں���
}
void ZeroCheck_Init_Interface(ZeroCheck_Typedef *zeroCheck,float CountCycle)
{
	zeroCheck->ActualValue = 0;
	zeroCheck->CountCycle  = CountCycle;
	zeroCheck->LastValue   = 0;
	zeroCheck->PreError    = 0;
	zeroCheck->Circle = 0;
}
/*
 * @brief ��������ֵ����
 * @param ��Ҫ����Ľṹ���header
 * */
float ResetZeroCheck(ZeroCheck_Typedef *zeroCheck)
{
	float temp = zeroCheck->CountCycle;
	ZeroCheck_Init_Interface(zeroCheck,temp);
	return 1;
}

/**
  * @brief  λ��ʽ���ٶ�ʽ������
	           Zero->ActualValue ��ʾ�������ǰֵ
						 Zero->LastValue ��ʾ�������һ��ֵ
						 Zero->CountCycle ��ʾ���������ʱԽ��ֵ������������
						 Zero->PreError ��ʾ�������ֵ
						 ʹ�ô˺���ǰҪ������Ӧ������ṹ��� Zero->CountCycle��Zero->LastValue
  * @param  ZeroCheck_Typedef *Zero  ������ṹ��
  *         float value  �������
            short Zerocheck_mode��ȡֵPosition��Speed
  * @retval ȡ����Zerocheck_mode���ֱ�����������λ��ֵ���ٶ�ֵ
  */
float ZeroCheck_cal(ZeroCheck_Typedef *Zero,float value)
{
	Zero->ActualValue=value;
	
	Zero->PreError=Zero->ActualValue-Zero->LastValue;
	Zero->LastValue=Zero->ActualValue;
	
	if(Zero->PreError>0.7f*Zero->CountCycle)
	{
		Zero->PreError=Zero->PreError-Zero->CountCycle;
		Zero->Circle++;
	}
	if(Zero->PreError<-0.7f*Zero->CountCycle)
	{
		Zero->PreError=Zero->PreError+Zero->CountCycle;
		Zero->Circle--;
	}
	return Zero->ActualValue - Zero->Circle*Zero->CountCycle;
}

