#include "ZeroCheck.h"

float Get_ZeroCheck_Value_Interface(ZeroCheck_Typedef *zero,float value)
{
		return ZeroCheck_cal(zero,value);//调用datareceive的接口函数
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
 * @brief 将过零检测值置零
 * @param 需要置零的结构体的header
 * */
float ResetZeroCheck(ZeroCheck_Typedef *zeroCheck)
{
	float temp = zeroCheck->CountCycle;
	ZeroCheck_Init_Interface(zeroCheck,temp);
	return 1;
}

/**
  * @brief  位置式和速度式过零检测
	           Zero->ActualValue 表示检测量当前值
						 Zero->LastValue 表示检测量上一次值
						 Zero->CountCycle 表示检测量过零时越变值，即计数周期
						 Zero->PreError 表示检测量差值
						 使用此函数前要申明对应检测量结构体的 Zero->CountCycle与Zero->LastValue
  * @param  ZeroCheck_Typedef *Zero  过零检测结构体
  *         float value  待检测量
            short Zerocheck_mode：取值Position或Speed
  * @retval 取决于Zerocheck_mode，分别输出过零检测后位置值或速度值
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

