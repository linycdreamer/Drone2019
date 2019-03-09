#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"
typedef struct UART_HandleTypeDef
{	
	USART_TypeDef *UART_BASEx;
	USART_InitTypeDef UARTx;
	GPIO_InitTypeDef  UARTx_Tx;
	GPIO_InitTypeDef  UARTx_Rx;
}UART_HandleTypeDef;
void USART_Config(void);
void UART_Config(UART_HandleTypeDef *uart,uint32_t USART_BaudRate,
	          uint16_t USART_WordLength,uint16_t USART_StopBits,
              uint16_t USART_Parity,uint16_t USART_Mode);
void UART_GPIO_RX_Config(UART_HandleTypeDef *uart,uint16_t GPIO_PinRx,GPIO_TypeDef *GPIORx);
void UART_GPIO_TX_Config(UART_HandleTypeDef *uart,uint16_t GPIO_PinTx,GPIO_TypeDef *GPIOTx);
#endif

