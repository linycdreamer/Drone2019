/**
  ******************************************************************************
  * @file GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_dma.h"
#include "dbus.h"
#include "drv_can.h"
#define RX_USART3_BUFFER 30
/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/*
  USART1中断服务程序
*/					  
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)  
	{  
		USART_ClearITPendingBit(USART2,USART_FLAG_TC);//清除发送完成标志位
	} 
}
/*
  USART2中断服务程序
*/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)  
	{  
		USART_ClearITPendingBit(USART2,USART_FLAG_TC);//清除发送完成标志位
	} 
}
/*
  USART3中断服务程序
*/
uint8_t tempData[18];
short temp_1;
void USART3_IRQHandler(void)
{
	static int DATA_LENGTH=0;
//	if (USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	if (USART3->SR>>4&0x01)//闲时中断
	{
		(void)USART3->SR;
		(void)USART3->DR;	
//		DMA_Cmd(DMA1_Channel3,DISABLE);
		DATA_LENGTH = RX_USART3_BUFFER - DMA_GetCurrDataCounter(DMA1_Channel3);
		if(DATA_LENGTH==18)
		{
			RemoteReceive();
			DMA_SetCurrDataCounter(DMA1_Channel3,RX_USART3_BUFFER);	
		}
//		DMA_Cmd(DMA1_Channel3,ENABLE);
//		DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,ENABLE);
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
    }
}
/*
  USART4中断服务程序
*/
void UART4_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)  
	{  
		USART_ClearITPendingBit(USART2,USART_FLAG_TC);//清除发送完成标志位
	} 
}
/*
  USART5中断服务程序
*/
void UART5_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)  
	{  
		USART_ClearITPendingBit(USART2,USART_FLAG_TC);//清除发送完成标志位
	} 
}
void DMA2_Channel2_IRQHandler(void)
{
    if(DMA_GetFlagStatus(DMA2_FLAG_TC2)==SET)
	{
		DMA_ClearITPendingBit(DMA2_IT_TC2);
	}
}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rx_message;
//	if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
//	{
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		Can1Receive_Hook(&rx_message);
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);

//	}
}	
//void CAN1_RX0_IRQHandler(void)
//{
//		CanRxMsg RxMessage;

//		RxMessage.StdId=0x00;
//		RxMessage.ExtId=0x00;
//		RxMessage.RTR=CAN_RTR_DATA;  // 数据帧or远程
//		RxMessage.IDE=CAN_ID_STD;	 // 标准or扩展
//		RxMessage.DLC=0;
//		RxMessage.FMI=0;
//		RxMessage.Data[0]=0x00;
//		RxMessage.Data[1]=0x00;

//		CAN_Receive(CAN1,CAN_FIFO0, &RxMessage);	 // CAN接收数据		
//	
//}
void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg rx_message_0;
	if(CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
	{
        CAN_Receive(CAN2, CAN_FIFO0, &rx_message_0);	
		CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
		
	}
}								 								
void CAN2_RX1_IRQHandler(void)
{
		CanRxMsg RxMessage;
		CAN_Receive(CAN2,CAN_FIFO1, &RxMessage);	 // CAN接收数据	
        Can2Receive_Hook(&RxMessage,1);
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
