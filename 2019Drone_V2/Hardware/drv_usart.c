#include "drv_dma.h"
#include "drv_nvic.h"
#include "drv_usart.h"
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
uint8_t uart1_RxBuffer[8];
uint8_t uart1_TxBuffer[8];
uint8_t uart2_RxBuffer[8];
uint8_t uart2_TxBuffer[8];
uint8_t uart3_RxBuffer[18];
/*
 * USART1 -- TX->PA9 RX->PA10
 * USART2 -- TX->PA2 RX->PA3
 * USART3 -- RX->PB11
 * UART4 --- TX->PC10 RX->PC11
 * UART5 --- TX->PC12 RX->PD2
 * */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;  
    USART_InitTypeDef USART_InitStrue;  
    NVIC_InitTypeDef NVIC_InitStrue;  

	huart1.UART_BASEx = USART1;
	huart2.UART_BASEx = USART2;
	huart3.UART_BASEx = USART3;
	huart4.UART_BASEx = UART4;
	huart5.UART_BASEx = UART5;
	{//tim
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3|RCC_APB1Periph_UART4|RCC_APB1Periph_UART5,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
	    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	}
	{//GPIO
		UART_GPIO_RX_Config(&huart1,GPIO_Pin_10,GPIOA);
		UART_GPIO_TX_Config(&huart1,GPIO_Pin_9,GPIOA);
		UART_GPIO_RX_Config(&huart2,GPIO_Pin_3,GPIOA);
		UART_GPIO_TX_Config(&huart2,GPIO_Pin_2,GPIOA);
		UART_GPIO_RX_Config(&huart3,GPIO_Pin_11,GPIOB);
		UART_GPIO_RX_Config(&huart4,GPIO_Pin_11,GPIOC);
		UART_GPIO_TX_Config(&huart4,GPIO_Pin_10,GPIOC);
		UART_GPIO_RX_Config(&huart5,GPIO_Pin_12,GPIOC);
		UART_GPIO_TX_Config(&huart5,GPIO_Pin_2,GPIOD);
	}
	{//NVIC
		NVIC_Config(USART1_IRQn, 1, 1);
		NVIC_Config(USART2_IRQn, 1, 1);
		NVIC_Config(USART3_IRQn, 1, 1);
		NVIC_Config(UART4_IRQn, 1, 1);
		NVIC_Config(UART5_IRQn, 1, 1);
	}
	{//DMA
		DMA_Config(DMA1_Channel5,(uint32_t)&huart1.UART_BASEx->DR,(uint32_t)uart1_RxBuffer,DMA_DIR_PeripheralSRC,8,
		           DMA_PeripheralInc_Disable,DMA_MemoryInc_Enable,DMA_PeripheralDataSize_HalfWord,DMA_MemoryDataSize_HalfWord,
                   DMA_Mode_Normal,DMA_Priority_Medium,DMA_M2M_Disable);
	    DMA_Config(DMA1_Channel4,(uint32_t)&huart1.UART_BASEx->DR,(uint32_t)uart1_TxBuffer,DMA_DIR_PeripheralDST,8,
		           DMA_PeripheralInc_Disable,DMA_MemoryInc_Enable,DMA_PeripheralDataSize_HalfWord,DMA_MemoryDataSize_HalfWord,
                   DMA_Mode_Normal,DMA_Priority_Medium,DMA_M2M_Disable);
		DMA_Config(DMA1_Channel6,(uint32_t)&huart2.UART_BASEx->DR,(uint32_t)uart2_RxBuffer,DMA_DIR_PeripheralSRC,8,
		           DMA_PeripheralInc_Disable,DMA_MemoryInc_Enable,DMA_PeripheralDataSize_HalfWord,DMA_MemoryDataSize_HalfWord,
                   DMA_Mode_Normal,DMA_Priority_Medium,DMA_M2M_Disable);
		DMA_Config(DMA1_Channel7,(uint32_t)&huart2.UART_BASEx->DR,(uint32_t)uart2_TxBuffer,DMA_DIR_PeripheralDST,8,
		           DMA_PeripheralInc_Disable,DMA_MemoryInc_Enable,DMA_PeripheralDataSize_HalfWord,DMA_MemoryDataSize_HalfWord,
                   DMA_Mode_Normal,DMA_Priority_Medium,DMA_M2M_Disable);
		DMA_Config(DMA1_Channel3,(uint32_t)&huart3.UART_BASEx->DR,(uint32_t)uart3_RxBuffer,DMA_DIR_PeripheralSRC,30,
		           DMA_PeripheralInc_Disable,DMA_MemoryInc_Enable,DMA_PeripheralDataSize_Byte,DMA_MemoryDataSize_Byte,
                   DMA_Mode_Circular,DMA_Priority_Medium,DMA_M2M_Disable);
		
		DMA_Cmd(DMA1_Channel3,ENABLE);
		USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
		USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
		USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
		USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
	}
	{//UART
//		UART_Config(&huart1, 115200,8,USART_StopBits_1,USART_Parity_Even,USART_Mode_Tx|USART_Mode_Rx);
//		UART_Config(&huart2,115200,8,USART_StopBits_1,USART_Parity_Even,USART_Mode_Tx|USART_Mode_Rx);
		UART_Config(&huart3,100000,8,USART_StopBits_1,USART_Parity_Even,USART_Mode_Rx);
//		UART_Config(&huart4,115200,8,USART_StopBits_1,USART_Parity_Even,USART_Mode_Tx|USART_Mode_Rx);
//		UART_Config(&huart5,115200 ,8,USART_StopBits_1,USART_Parity_Even,USART_Mode_Tx|USART_Mode_Rx);

		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);
		USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
		USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	}
	USART_Cmd(USART3,ENABLE);
}
/**
  * @brief  Initializes the USARTx peripheral 
  * @param  USART_BaudRate: 
  *         @arg 9600
  *         @arg 115200
  *         @arg 100000
  * @param  USART_WordLength: 
  *         @arg USART_WordLength_8b                 
  *         @arg USART_WordLength_9b                
  * @param  USART_StopBits: 
  *         @arg USART_StopBits_1                     
  *         @arg USART_StopBits_0_5                 
  *         @arg USART_StopBits_2                   
  *         @arg USART_StopBits_1_5              
  * @param  USART_Parity: 
  *         @arg USART_Parity_No                     
  *         @arg USART_Parity_Even                   
  *         @arg USART_Parity_Odd                    
  * @param  USART_Mode: 
  *         @arg USART_Mode_Rx                      
  *         @arg USART_Mode_Tx    
  *         @arg USART_Mode_Tx|USART_Mode_Rx     
  * @retval None
  */
void UART_Config(UART_HandleTypeDef *uart,uint32_t USART_BaudRate,
	           uint16_t USART_WordLength,uint16_t USART_StopBits,
               uint16_t USART_Parity,uint16_t USART_Mode)
{
	uart->UARTx.USART_BaudRate = USART_BaudRate;
	uart->UARTx.USART_WordLength = USART_WordLength;
	uart->UARTx.USART_StopBits = USART_StopBits;
	uart->UARTx.USART_Parity = USART_Parity;
	uart->UARTx.USART_Mode = USART_Mode;
	uart->UARTx.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(uart->UART_BASEx,&uart->UARTx);
}
/**
  * @brief  Initializes the GPIOx for usart RX
  * @param  GPIO_PinRx: GPIO_Pin_x,where x can be (0..15) to select the GPIO pin.      
  * @param  GPIORx :GPIOx,where x can be (A..G) to select the GPIO peripheral.
  * @retval None
  */
void UART_GPIO_RX_Config(UART_HandleTypeDef *uart, 
	                uint16_t GPIO_PinRx,GPIO_TypeDef *GPIORx)
{
	uart->UARTx_Rx.GPIO_Pin = GPIO_PinRx;
	uart->UARTx_Rx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	uart->UARTx_Rx.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIORx,&uart->UARTx_Rx); 
}
/**
  * @brief  Initializes the GPIOx for usart TX
  * @param  GPIO_PinTx: GPIO_Pin_x,where x can be (0..15) to select the GPIO pin.      
  * @param  GPIOTx :GPIOx,where x can be (A..G) to select the GPIO peripheral.
  * @retval None
  */
void UART_GPIO_TX_Config(UART_HandleTypeDef *uart, 
	                uint16_t GPIO_PinTx,GPIO_TypeDef *GPIOTx)
{
	uart->UARTx_Tx.GPIO_Pin = GPIO_PinTx;
	uart->UARTx_Tx.GPIO_Mode = GPIO_Mode_AF_PP;
	uart->UARTx_Tx.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOTx,&uart->UARTx_Tx); 
}

