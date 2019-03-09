#ifndef __TIM_H__
#define __TIM_H__
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
typedef struct TIM_HandleTypeDef
{	
    TIM_TimeBaseInitTypeDef Tim_Base;
	TIM_TypeDef *Tim;
	TIM_OCInitTypeDef Tim_OC;
	TIM_ICInitTypeDef Tim_IC;
//	TIM_BDTRInitTypeDef Tim_BD;
	GPIO_InitTypeDef  TIMx_CH1;
	GPIO_InitTypeDef  TIMx_CH2;
	GPIO_InitTypeDef  TIMx_CH3;
	GPIO_InitTypeDef  TIMx_CH4;
}TIM_HandleTypeDef;//目前只用到输出PWM的功能
void TIM_Config(void);
void TIM_BASE_Config(TIM_HandleTypeDef * tim,uint16_t TIM_Prescaler,uint16_t TIM_CounterMode,
	                 uint16_t TIM_Period,uint16_t TIM_ClockDivision,uint8_t TIM_RepetitionCounter);
void TIM_OC_Config(TIM_HandleTypeDef * tim,uint16_t TIM_OCMode,uint16_t TIM_OutputState,
	               uint16_t TIM_OutputNState,uint16_t TIM_Pulse,uint16_t TIM_OCPolarity,
                   uint16_t TIM_OCNPolarity,uint16_t TIM_OCIdleState,uint16_t TIM_OCNIdleState);
void TIM_IC_Config(TIM_HandleTypeDef * tim);
void TIM_GPIO_Config(TIM_HandleTypeDef * tim,int channel,
	 uint16_t GPIO_Pinx,GPIO_TypeDef *GPIOx);
void delayMs_Block(unsigned int t);
void delayUs_Block(unsigned int t);

#endif

