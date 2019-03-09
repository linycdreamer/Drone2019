#include "drv_can.h"
CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;
uint8_t Can1ReceiveBuffer[5][8];//according can num
void CAN_SendData(CAN_HandleTypeDef *hcan,uint32_t id)
{
	CanTxMsg tx_message;
    tx_message.StdId = id;
    tx_message.IDE = CAN_ID_STD;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
 
    tx_message.Data[0] = hcan->SendBuffer[0];
    tx_message.Data[1] = hcan->SendBuffer[1];
    tx_message.Data[2] = hcan->SendBuffer[2];
    tx_message.Data[3] = hcan->SendBuffer[3];
    tx_message.Data[4] = hcan->SendBuffer[4];
    tx_message.Data[5] = hcan->SendBuffer[5];
    tx_message.Data[6] = hcan->SendBuffer[6];
    tx_message.Data[7] = hcan->SendBuffer[7];
    if(hcan->UniqueID == 1)
		CAN_Transmit(CAN1,&tx_message);
	else if(hcan->UniqueID == 2)
		CAN_Transmit(CAN2,&tx_message);
}
uint8_t* getCan1Msg(uint8_t num)
{
	return Can1ReceiveBuffer[num];
}
void Can1Receive_Hook(CanRxMsg *rxMsg)
{
	switch(rxMsg->StdId)
	{
		case 0x205:
			 for(int i=0;i<8;i++)
		        Can1ReceiveBuffer[0][i] = rxMsg->Data[i];
			break;
		case 0x206:
			for(int i=0;i<8;i++)
		        Can1ReceiveBuffer[1][i] = rxMsg->Data[i];
			break;		
	}
}
void Can2Receive_Hook(CanRxMsg *rxMsg,uint8_t fifox)
{
	if(fifox == 1)
	{//imu
		switch(rxMsg->StdId)
		{
			case 0x300:
				 for(int i=0;i<8;i++)
					Can1ReceiveBuffer[2][i] = rxMsg->Data[i];
				break;
			case 0x301:
				for(int i=0;i<8;i++)
					Can1ReceiveBuffer[3][i] = rxMsg->Data[i];
				break;		
	    }
	}
	else 
	{
		
	}
}
void CAN_Config(void)
{
//	{//clock
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
//	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1|RCC_APB1Periph_CAN2, ENABLE);
//	}
//	{//GPIO
//		hcan1.CAN_RX.GPIO_Pin = CAN1_Rx_Pin;
//		hcan1.CAN_TX.GPIO_Pin = CAN1_Tx_Pin;
//		hcan2.CAN_RX.GPIO_Pin = CAN2_Rx_Pin;
//		hcan2.CAN_TX.GPIO_Pin = CAN2_Tx_Pin;
//		
//		hcan1.CAN_RX.GPIO_Mode = GPIO_Mode_IPU;
//		hcan1.CAN_TX.GPIO_Mode = GPIO_Mode_AF_PP;
//		hcan2.CAN_RX.GPIO_Mode = GPIO_Mode_IPU;
//		hcan2.CAN_TX.GPIO_Mode = GPIO_Mode_AF_PP;
//		
//		hcan1.CAN_RX.GPIO_Speed = GPIO_Speed_50MHz;
//		hcan1.CAN_TX.GPIO_Speed = GPIO_Speed_50MHz;
//		hcan2.CAN_RX.GPIO_Speed = GPIO_Speed_50MHz;
//		hcan2.CAN_TX.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(CAN1_Rx_GPIO_Port, &hcan1.CAN_RX);
//		GPIO_Init(CAN1_Tx_GPIO_Port, &hcan1.CAN_TX);
//		GPIO_Init(CAN2_Rx_GPIO_Port, &hcan2.CAN_RX);
//		GPIO_Init(CAN2_Tx_GPIO_Port, &hcan2.CAN_TX);
//		GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);  // CAN1 remap
//	}
//	{//NVIC
//		hcan1.nvic.NVIC_IRQChannel=CAN1_RX0_IRQn;
//		hcan1.nvic.NVIC_IRQChannelPreemptionPriority = 0;
//		hcan1.nvic.NVIC_IRQChannelSubPriority = 0;
//		hcan1.nvic.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&hcan1.nvic);	
//		hcan2.nvic.NVIC_IRQChannel=CAN2_RX0_IRQn;
//		hcan2.nvic.NVIC_IRQChannelPreemptionPriority = 0;
//		hcan2.nvic.NVIC_IRQChannelSubPriority = 0;
//		hcan2.nvic.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&hcan2.nvic);	
//	}
//	{//CAN
//		CAN_DeInit(CAN1);
//		CAN_DeInit(CAN2);
//		CAN_StructInit(&hcan1.Init);   
//        CAN_StructInit(&hcan2.Init);
//		hcan1.Init.CAN_TTCM=DISABLE;
//		hcan1.Init.CAN_ABOM=DISABLE;
//		hcan1.Init.CAN_AWUM=DISABLE;
//		hcan1.Init.CAN_NART=DISABLE;
//		hcan1.Init.CAN_RFLM=DISABLE;
//		hcan1.Init.CAN_TXFP=DISABLE;
//		hcan1.Init.CAN_Mode=CAN_Mode_Normal;   
//		hcan1.Init.CAN_SJW=SET_CAN_SJW;
//		hcan1.Init.CAN_BS1=SET_CAN_BS1;  
//		hcan1.Init.CAN_BS2=SET_CAN_BS2;	
//		hcan1.Init.CAN_Prescaler=SET_CAN_PRES;
//        CAN_Init(CAN1,&hcan1.Init);	// CAN1	
//        
//		hcan2.Init.CAN_TTCM=DISABLE;
//		hcan2.Init.CAN_ABOM=DISABLE;
//		hcan2.Init.CAN_AWUM=DISABLE;
//		hcan2.Init.CAN_NART=DISABLE;
//		hcan2.Init.CAN_RFLM=DISABLE;
//		hcan2.Init.CAN_TXFP=DISABLE;
//		hcan2.Init.CAN_Mode=CAN_Mode_Normal;   
//		hcan2.Init.CAN_SJW=SET_CAN_SJW;
//		hcan2.Init.CAN_BS1=SET_CAN_BS1;  
//		hcan2.Init.CAN_BS2=SET_CAN_BS2;	
//		hcan2.Init.CAN_Prescaler=SET_CAN_PRES;
//        CAN_Init(CAN2,&hcan2.Init);	// CAN2		
//	}
//	{//filter
//		hcan1.filter.CAN_FilterNumber=0;	 
//		hcan1.filter.CAN_FilterMode=CAN_FilterMode_IdMask;	 // 标识符屏蔽位模式
//		hcan1.filter.CAN_FilterScale=CAN_FilterScale_32bit;   // 32位过滤器
//		hcan1.filter.CAN_FilterIdHigh=0x0000;			// 过滤器标识符
//		hcan1.filter.CAN_FilterIdLow=0x0000;				
//		hcan1.filter.CAN_FilterMaskIdHigh=0x0000;		// 过滤器屏蔽标识符
//		hcan1.filter.CAN_FilterMaskIdLow=0x0000;
//		hcan1.filter.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0指向过滤器
//		hcan1.filter.CAN_FilterActivation=ENABLE;
//		CAN_FilterInit(&hcan1.filter);

//		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);  // CAN1
//		
//		hcan2.filter.CAN_FilterNumber=14;	// 
//		hcan2.filter.CAN_FilterMode=CAN_FilterMode_IdMask;	 // 标识符屏蔽位模式
//		hcan2.filter.CAN_FilterScale=CAN_FilterScale_32bit;   // 32位过滤器
//		hcan2.filter.CAN_FilterIdHigh=0x0000;			// 过滤器标识符
//		hcan2.filter.CAN_FilterIdLow=0x0000;				
//		hcan2.filter.CAN_FilterMaskIdHigh=0x0000;		// 过滤器屏蔽标识符
//		hcan2.filter.CAN_FilterMaskIdLow=0x0000;
//		hcan2.filter.CAN_FilterFIFOAssignment=CAN_FIFO1;	 // FIFO1指向过滤器
//		hcan2.filter.CAN_FilterActivation=ENABLE;
//		CAN_FilterInit(&hcan2.filter);

//		CAN_ITConfig(CAN2,CAN_IT_FMP1,ENABLE);  // CAN2
//	}
	hcan1.UniqueID = 1;
    hcan2.UniqueID = 2;
	CAN1_Config(SET_CAN_SJW,SET_CAN_BS1,SET_CAN_BS2,SET_CAN_PRES);  		
    CAN2_Config(SET_CAN_SJW,SET_CAN_BS1,SET_CAN_BS2,SET_CAN_PRES);	
}
void CAN1_Config(uint8_t sjw,uint8_t bs1,uint8_t bs2,uint16_t pres)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		CAN_InitTypeDef        CAN_InitStructure;
		CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		/* 打开GPIO时钟、AFIO时钟，CAN时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);


		/* CAN1 RX PB8 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		/* CAN1 TX PB9 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);  // CAN1 remap

		/* CAN1 Enabling interrupt */									  
		NVIC_InitStructure.NVIC_IRQChannel=CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);									
									
		/* CAN  BaudRate = RCC_APB1PeriphClock/(CAN_SJW+CAN_BS1+CAN_BS2)/CAN_Prescaler */
		CAN_DeInit(CAN1);
		CAN_StructInit(&CAN_InitStructure);   

		CAN_InitStructure.CAN_TTCM=DISABLE;
		CAN_InitStructure.CAN_ABOM=DISABLE;
		CAN_InitStructure.CAN_AWUM=DISABLE;
		CAN_InitStructure.CAN_NART=DISABLE;
		CAN_InitStructure.CAN_RFLM=DISABLE;
		CAN_InitStructure.CAN_TXFP=DISABLE;
		CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;   
		//CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;
		CAN_InitStructure.CAN_SJW=sjw;
		CAN_InitStructure.CAN_BS1=bs1;  
		CAN_InitStructure.CAN_BS2=bs2;	
		CAN_InitStructure.CAN_Prescaler=pres;


		CAN_Init(CAN1,&CAN_InitStructure);	// CAN1											

		CAN_FilterInitStructure.CAN_FilterNumber=0;	 
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	 // 标识符屏蔽位模式
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32位过滤器
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;			// 过滤器标识符
		CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;				
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;		// 过滤器屏蔽标识符
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	 // FIFO0指向过滤器
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);
	

//    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
//    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
//	


}

/*****************************************
  CAN2 Config
  FIFO_1	  
  返回：
*****************************************/
void CAN2_Config(uint8_t sjw,uint8_t bs1,uint8_t bs2,uint16_t pres)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		CAN_InitTypeDef        CAN_InitStructure;
		CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		/* 打开GPIO时钟、AFIO时钟，CAN时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

		/* CAN2 RX PB12 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		/* CAN2 TX PB13 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);								

		/* CAN2 Enabling interrupt */								 	  
		NVIC_InitStructure.NVIC_IRQChannel=CAN2_RX1_IRQn;	// FIFO_1
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);								  	

		/* CAN  BaudRate = RCC_APB1PeriphClock/(CAN_SJW+CAN_BS1+CAN_BS2)/CAN_Prescaler */
		CAN_DeInit(CAN2);
		CAN_StructInit(&CAN_InitStructure);   

		CAN_InitStructure.CAN_TTCM=DISABLE;
		CAN_InitStructure.CAN_ABOM=DISABLE;
		CAN_InitStructure.CAN_AWUM=DISABLE;
		CAN_InitStructure.CAN_NART=DISABLE;
		CAN_InitStructure.CAN_RFLM=DISABLE;
		CAN_InitStructure.CAN_TXFP=DISABLE;
		CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;   
		//CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;
		CAN_InitStructure.CAN_SJW=sjw;
		CAN_InitStructure.CAN_BS1=bs1;  
		CAN_InitStructure.CAN_BS2=bs2;	
		CAN_InitStructure.CAN_Prescaler=pres;

		CAN_Init(CAN2,&CAN_InitStructure);   // CAN2													

		CAN_FilterInitStructure.CAN_FilterNumber=14;	// 
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	 // 标识符屏蔽位模式
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   // 32位过滤器
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;			// 过滤器标识符
		CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;				
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;		// 过滤器屏蔽标识符
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO1;	 // FIFO1指向过滤器
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);

		CAN_ITConfig(CAN2,CAN_IT_FMP1,ENABLE);  // CAN2
}
