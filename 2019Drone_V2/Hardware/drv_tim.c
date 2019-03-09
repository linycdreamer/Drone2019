#include "driver.h"
#include "dshot.h"
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
extern union
{
   uint8_t sendBuffer[2*ESC_CMD_BUFFER_LEN];
   uint32_t DMA_sendBuffer[ESC_CMD_BUFFER_LEN/2];
}dshotBuffer;
void TIM_Config(void)
{
	htim5.Tim = TIM5;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
	TIM_GPIO_Config(&htim5,1,GPIO_Pin_0,GPIOA);
	TIM_GPIO_Config(&htim5,2,GPIO_Pin_1,GPIOA);
	TIM_BASE_Config(&htim5,4-1,TIM_CounterMode_Up,30-1,TIM_CKD_DIV1,0);//72M
	TIM_OC_Config(&htim5,TIM_OCMode_PWM1,TIM_OutputState_Enable,TIM_OutputNState_Disable,0,TIM_OCPolarity_High,
                   TIM_OCNPolarity_High,TIM_OCIdleState_Reset,TIM_OCNIdleState_Reset);
	TIM_OC1Init(htim5.Tim,&htim5.Tim_OC);
	TIM_OC2Init(htim5.Tim,&htim5.Tim_OC);
	TIM_OC1PreloadConfig(htim5.Tim,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(htim5.Tim,TIM_OCPreload_Enable);
	
	DMA_Config(DMA2_Channel2,(uint32_t)&(TIM5->DMAR),(uint32_t)dshotBuffer.DMA_sendBuffer,DMA_DIR_PeripheralDST,36,
		           DMA_PeripheralInc_Disable,DMA_MemoryInc_Enable,DMA_PeripheralDataSize_Word,DMA_PeripheralDataSize_Word,
                   DMA_Mode_Circular,DMA_Priority_Medium,DMA_M2M_Disable);
//	DMA_ITConfig(DMA2_Channel2,DMA_IT_TC,ENABLE);
//	NVIC_Config(DMA2_Channel2_IRQn,2,3);
    TIM_DMAConfig(TIM5,TIM_DMABase_CCR1,TIM_DMABurstLength_2Transfers);
	TIM_DMACmd(TIM5,TIM_DMA_Update,ENABLE);
	DMA_Cmd(DMA2_Channel2,ENABLE);	
	TIM_ARRPreloadConfig(htim5.Tim, ENABLE);
	TIM_Cmd(htim5.Tim,ENABLE);
	TIM_CtrlPWMOutputs(htim5.Tim,ENABLE);
}
/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to the parameters 
  * @param  TIMx: where x can be 1 to 17 to select the TIM peripheral.
  * @param TIM_Prescaler          Specifies the prescaler value used to divide the TIM clock.
  *                                    This parameter can be a number between 0x0000 and 0xFFFF 
  * @param TIM_CounterMode       Specifies the counter mode. 
  *        @arg TIM_CounterMode_Up                 
  *        @arg TIM_CounterMode_Down              
  *        @arg TIM_CounterMode_CenterAligned1     
  *        @arg TIM_CounterMode_CenterAligned2     
  *        @arg TIM_CounterMode_CenterAligned3     
  * @param TIM_Period             Specifies the period value to be loaded into the active
  *                                     Auto-Reload Register at the next update event.
  *                                     This parameter must be a number between 0x0000 and 0xFFFF. 
  * @param TIM_ClockDivision      Specifies the clock division.
  *        @arg TIM_CKD_DIV1                       
  *        @arg TIM_CKD_DIV2                      
  *        @arg TIM_CKD_DIV4                      
  * @param TIM_RepetitionCounter   Specifies the repetition counter value. Each time the RCR downcounter
  *                                     reaches zero, an update event is generated and counting restarts
  *                                     from the RCR value (N).
  *                                     This means in PWM mode that (N+1) corresponds to:
  *                                        - the number of PWM periods in edge-aligned mode
  *                                        - the number of half PWM period in center-aligned mode
  *                                     This parameter must be a number between 0x00 and 0xFF. 
  *                                     @note This parameter is valid only for TIM1 and TIM8. 
  * @retval None
  */
void TIM_BASE_Config(TIM_HandleTypeDef * tim,uint16_t TIM_Prescaler,uint16_t TIM_CounterMode,
	                 uint16_t TIM_Period,uint16_t TIM_ClockDivision,uint8_t TIM_RepetitionCounter)
{
	tim->Tim_Base.TIM_Prescaler = TIM_Prescaler;
	tim->Tim_Base.TIM_CounterMode = TIM_CounterMode;
	tim->Tim_Base.TIM_Period = TIM_Period;
	tim->Tim_Base.TIM_ClockDivision = TIM_ClockDivision;
	tim->Tim_Base.TIM_RepetitionCounter = TIM_RepetitionCounter;
	TIM_TimeBaseInit(tim->Tim,&tim->Tim_Base);
}
/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to the parameters 
  * @param TIM_OCMode         Specifies the TIM mode.
  *        @arg TIM_OCMode_Timing                  
  *        @arg TIM_OCMode_Active                 
  *        @arg TIM_OCMode_Inactive              
  *        @arg TIM_OCMode_Toggle                  
  *        @arg TIM_OCMode_PWM1                  
  *        @arg TIM_OCMode_PWM2                                  
  * @param TIM_OutputState    Specifies the TIM Output Compare state.
  *        @arg TIM_OutputState_Disable         
  *        @arg TIM_OutputState_Enable                                    
  * @param TIM_OutputNState   Specifies the TIM complementary Output Compare state.              
  *                                @note This parameter is valid only for TIM1 and TIM8. 
  *        @arg TIM_OutputNState_Disable          
  *        @arg TIM_OutputNState_Enable           
  * @param TIM_Pulse          Specifies the pulse value to be loaded into the Capture Compare Register. 
  *                                This parameter can be a number between 0x0000 and 0xFFFF 
  * @param TIM_OCPolarity     Specifies the output polarity.
  *        @arg TIM_OCPolarity_High              
  *        @arg TIM_OCPolarity_Low               
  * @param TIM_OCNPolarity    Specifies the complementary output polarity.                   
  *                                @note This parameter is valid only for TIM1 and TIM8. 
  *        @arg TIM_OCNPolarity_High               
  *        @arg TIM_OCNPolarity_Low               
  * @param TIM_OCIdleState    Specifies the TIM Output Compare pin state during Idle state.
  *                                @note This parameter is valid only for TIM1 and TIM8. 
  *        @arg TIM_OCIdleState_Set                
  *        @arg TIM_OCIdleState_Reset              
  * @param TIM_OCNIdleState   Specifies the TIM Output Compare pin state during Idle state.
  *                                @note This parameter is valid only for TIM1 and TIM8. 
  *        @arg TIM_OCNIdleState_Set              
  *        @arg TIM_OCNIdleState_Reset            
  * @retval None
  */
void TIM_OC_Config(TIM_HandleTypeDef * tim,uint16_t TIM_OCMode,uint16_t TIM_OutputState,
	               uint16_t TIM_OutputNState,uint16_t TIM_Pulse,uint16_t TIM_OCPolarity,
                   uint16_t TIM_OCNPolarity,uint16_t TIM_OCIdleState,uint16_t TIM_OCNIdleState)
{
	tim->Tim_OC.TIM_OCMode = TIM_OCMode;
	tim->Tim_OC.TIM_OutputState = TIM_OutputState;
	tim->Tim_OC.TIM_OutputNState = TIM_OutputNState;
	tim->Tim_OC.TIM_Pulse = TIM_Pulse;
	tim->Tim_OC.TIM_OCPolarity = TIM_OCPolarity;
	tim->Tim_OC.TIM_OCNPolarity = TIM_OCNPolarity;
	tim->Tim_OC.TIM_OCIdleState = TIM_OCIdleState;
	tim->Tim_OC.TIM_OCNIdleState = TIM_OCNIdleState;
}
//wait...
void TIM_IC_Config(TIM_HandleTypeDef * tim)
{
	
}
/**
  * @brief  Initializes the GPIOx for PWM out
  * @param  GPIO_Pinx: GPIO_Pin_x,where x can be (0..15) to select the GPIO pin.      
  * @param  GPIOx :GPIOx,where x can be (A..G) to select the GPIO peripheral.
  * @retval None
  */
void TIM_GPIO_Config(TIM_HandleTypeDef * tim,int channel,
	 uint16_t GPIO_Pinx,GPIO_TypeDef *GPIOx)
{
	switch (channel)
	{
		case 1:
			tim->TIMx_CH1.GPIO_Pin = GPIO_Pinx;
		    tim->TIMx_CH1.GPIO_Mode = GPIO_Mode_AF_PP;
		    tim->TIMx_CH1.GPIO_Speed = GPIO_Speed_50MHz;
		    GPIO_Init(GPIOx,&tim->TIMx_CH1);
			break;
		case 2:
			tim->TIMx_CH2.GPIO_Pin = GPIO_Pinx;
		    tim->TIMx_CH2.GPIO_Mode = GPIO_Mode_AF_PP;
		    tim->TIMx_CH2.GPIO_Speed = GPIO_Speed_50MHz;
		    GPIO_Init(GPIOx,&tim->TIMx_CH2);
			break;
		case 3:
			tim->TIMx_CH3.GPIO_Pin = GPIO_Pinx;
		    tim->TIMx_CH3.GPIO_Mode = GPIO_Mode_AF_PP;
		    tim->TIMx_CH3.GPIO_Speed = GPIO_Speed_50MHz;
		    GPIO_Init(GPIOx,&tim->TIMx_CH3);
			break;
		case 4:
			tim->TIMx_CH4.GPIO_Pin = GPIO_Pinx;
		    tim->TIMx_CH4.GPIO_Mode = GPIO_Mode_AF_PP;
		    tim->TIMx_CH4.GPIO_Speed = GPIO_Speed_50MHz;
		    GPIO_Init(GPIOx,&tim->TIMx_CH4);
			break;
		default:
			break;
	}
}
void delayMs_Block(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=10300;
 		while(a--);
	}
}
void delayUs_Block(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=9;
		while(a--);
	}
}





