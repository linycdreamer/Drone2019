
#ifndef __CAN_H__
#define __CAN_H__

#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "misc.h"

typedef struct __CAN_HandleTypeDef
{	
	CAN_InitTypeDef   Init;                     
	GPIO_InitTypeDef  CAN_RX;
	GPIO_InitTypeDef  CAN_TX; 	
	CAN_FilterInitTypeDef filter;
	NVIC_InitTypeDef nvic;
	uint8_t UniqueID;
	uint8_t SendBuffer[8];
	uint8_t ReceiveBuffer[8];
} CAN_HandleTypeDef;
/***********GPIO宏定义 CAN1 ***********/
#define CAN1_Rx_Pin       GPIO_Pin_8
#define CAN1_Rx_GPIO_Port GPIOB
#define CAN1_Tx_Pin       GPIO_Pin_9
#define CAN1_Tx_GPIO_Port GPIOB
/***********GPIO宏定义 CAN2 ***********/
#define CAN2_Rx_Pin GPIO_Pin_12
#define CAN2_Rx_GPIO_Port GPIOB
#define CAN2_Tx_Pin GPIO_Pin_13
#define CAN2_Tx_GPIO_Port GPIOB

/********* CAN波特率  BaudRate = RCC_APB1PeriphClock/(CAN_SJW+CAN_BS1+CAN_BS2)/CAN_Prescaler 
********** 1M波特率 ***********/
#define    SET_CAN_SJW   CAN_SJW_1tq
#define    SET_CAN_BS1   CAN_BS1_5tq	
#define    SET_CAN_BS2   CAN_BS2_3tq	
#define    SET_CAN_PRES  4				

void CAN_Config(void);
void CAN_SendData(CAN_HandleTypeDef *hcan,uint32_t id);
void CAN_GetData(CAN_HandleTypeDef *hcan,uint32_t id);
void Can1Receive_Hook(CanRxMsg *rxMsg);
void Can2Receive_Hook(CanRxMsg *rxMsg0,uint8_t fifox);
uint8_t* getCan1Msg(uint8_t num);
void CAN1_Config(uint8_t sjw,uint8_t bs1,uint8_t bs2,uint16_t pres);
void CAN2_Config(uint8_t sjw,uint8_t bs1,uint8_t bs2,uint16_t pres);
#endif
